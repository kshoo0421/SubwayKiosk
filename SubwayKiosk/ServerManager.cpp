#include "ServerManager.h"

// 서버 연결용

ServerManager::ServerManager() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        qDebug() << "WSAStartup failed.\n";
        exit(1);
    }
#endif

    /*====== 여길 수정하시면 됩니다 ==========*/

    // ConnectToServer(); // 서버 연결

    /*===================================*/

}

ServerManager::~ServerManager() {
#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif

}

void ServerManager::ConnectToServer() {
    // 1. 소켓 생성
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr << "Socket creation failed.\n";
        #ifdef _WIN32
            WSACleanup();
        #endif
        exit(1);
    }

    // 2. 서버 주소 설정
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(SERVER_PORT);
    servAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    // 3. 서버 연결
    if (connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        std::cerr << "Connection failed.\n";
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        exit(1);
    }
}

int ServerManager::SendJsonToServer(const json& j) {
    string json_data = JsonToString(j); // string으로 변환
    string request = "POST / HTTP/1.1\r\n"
            "Host: " + string(SERVER_ADDR) + "\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + to_string(json_data.length())
            + "\r\n\r\n" + json_data;

    // 5. 서버에 요청 전송
    send(sock, request.c_str(), request.length(), 0);
    qDebug() << "JSON data sent to server";
    
    // 6. 응답 받기
    string sJsonResponse = ReceiveDataFromServer();
    int waitingNum;
    json jsonResponse = StringToJson(jsonResponse);
    jsonResponse.at("waiting number").get_to(waitingNum);
    return waitingNum;
}

string ServerManager::ReceiveDataFromServer() {
    buffer.assign(BUFFER_SIZE, ' ');
    int valRead = recv(sock, &buffer[0], BUFFER_SIZE, 0);  // Windows에서는 recv() 사용
    if (valRead > 0) {
        // 버퍼를 문자열로 변환 후 출력
        string response(buffer.begin(), buffer.begin() + valRead);
        cout << "Server response:\n" << response << endl;

        // HTTP 요청에서 본문 추출
        size_t contentPos = response.find("\r\n\r\n");
        string jsonBody = "";
        if (contentPos != string::npos) {
            jsonBody = response.substr(contentPos + 4);
        }

        return jsonBody;  // json 문자열 반환
    }
    else if (valRead == 0) {
        cout << "Connection closed by server." << endl;
    }
    else {
        cerr << "Failed to receive response from server. Error code: " << WSAGetLastError() << endl;
    }
    return "";  // 오류 시 빈 문자열 반환
}

json ServerManager::StringToJson(const string& s) {
    try {
        json jsonObject = json::parse(s);
        return jsonObject;
    } catch (const json::parse_error& e) {
        qDebug() << "JSON 파싱 오류";
        return json{{"error", "Parsing Error"}};
    }
}

// Cart->json nlohmann/json 오버라이드 
void to_json(json& j, const Sandwich& sandwich) {
    struct select selection = sandwich.GetSelected();

    short bitTopping = 0;
    short bitVegetable = 0;
    short bitSauce = 0;
    
    for(int i = 0; i < 14; i++) { // 비트마스킹
        if(i < 7 && selection.topping[i]) {
            bitTopping |= (1 << i);  // i번째 비트를 1로 설정
        }
        
        if(i < 8 && selection.vegetable[i]) {
                bitVegetable |= (1 << i);  // i번째 비트를 1로 설정
        }

        if (selection.sauce[i]) {
            bitSauce |= (1 << i);  // i번째 비트를 1로 설정
        }
    }

    j = json{{"Main Sandwich", selection.menu},
        {"Is 15cm?", selection.is15}, 
        {"Bread", selection.bread},
        {"Topping", bitTopping},
        {"Cheese", selection.cheese},
        {"Vegetable", bitVegetable},
        {"Sauce", bitSauce},
        {"Is Set", selection.isSet},
        {"Cookie", selection.cookie},
        {"Drink", selection.drink},
        {"Chips", selection.chips}
     };
}

// from_json 함수도 정의할 수 있음 (JSON -> Person 변환)
void from_json(const json& j, Sandwich& sandwich) {
    struct select& selection = sandwich.selection;

    short bitTopping = 0;
    short bitVegetable = 0;
    short bitSauce = 0;

    j.at("Main Sandwich").get_to(selection.menu);
    j.at("Is 15cm?").get_to(selection.is15);
    j.at("Bread").get_to(selection.bread);
    j.at("Topping").get_to(bitTopping);
    j.at("Cheese").get_to(selection.cheese);
    j.at("Vegetable").get_to(bitVegetable);
    j.at("Sauce").get_to(bitSauce);
    j.at("Is Set").get_to(selection.isSet);
    j.at("Cookie").get_to(selection.cookie);
    j.at("Drink").get_to(selection.drink);
    j.at("Chips").get_to(selection.chips);

    for(int i = 0; i < 14; i++) { // 비트마스킹
        if(i < 7) {
            selection.topping[i] = ((bitTopping & (1 << i)) != 0);
        }
        
        if(i < 8) {
            selection.vegetable[i] = ((bitVegetable & (1 << i)) != 0);
        }
        
        selection.sauce[i] = ((bitSauce & (1 << i)) != 0); 
    }
}

void ServerManager::SendCartToServer(const Cart& cart) {
    json jSandwich = cart.GetSandwiches();
    json jChips = cart.GetChips();
    json jCookie = cart.GetCookies();
    json jDrinks = cart.GetDrinks();
    json jTotal = json{{"Type", "Cart"},
            {"Sandwiches", jSandwich},
            {"Chips", jChips},
            {"Cookies", jCookie},
            {"Drinks", jDrinks},
            {"Total Count", cart.totalCnt},
            {"Total Price", cart.totalPrice}
        };
    SendJsonToServer(jTotal);
}


string ServerManager::CartToJsonString(const Cart& cart) {
    qDebug() << "CartToJsonString";
    json jSandwich = cart.GetSandwiches();
    json jChips = cart.GetChips();
    json jCookie = cart.GetCookies();
    json jDrinks = cart.GetDrinks();
    json jTotal = json{{"Type", "Cart"},
        {"Sandwiches", jSandwich},
        {"Chips", jChips},
        {"Cookies", jCookie},
        {"Drinks", jDrinks},
        {"Total Count", cart.totalCnt},
        {"Total Price", cart.totalPrice}
    };
    return JsonToString(jTotal);
}

void ServerManager::StringToCart(Cart& cart, const string& sJson) {
    json j = StringToJson(sJson);
    j.at("Sandwiches").get_to(cart.sandwich);
    j.at("Chips").get_to(cart.chips);
    j.at("Cookies").get_to(cart.cookie);
    j.at("Drinks").get_to(cart.drinks);
    j.at("Total Count").get_to(cart.totalCnt);
    j.at("Total Price").get_to(cart.totalPrice);
}