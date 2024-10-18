#include "ServerManager.h"

// 서버 연결용
#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

ServerManager::ServerManager() {
    ConnectToServer(); // 서버 연결
}

ServerManager::~ServerManager() {
    close(sock);    // 소켓 닫기
}

void ServerManager::ConnectToServer() {
    // 1. 소켓 생성
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "Socket creation error" << endl;
        exit(1);
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(8080);

    // 2. 서버 주소 설정
    if (inet_pton(AF_INET, SERVER_ADDR, &servAddr.sin_addr) <= 0) {
        cerr << "Invalid address/ Address not supported" << endl;
        exit(1);
    }

    // 3. 서버 연결
    if (connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        cerr << "Connection Failed" << endl;
        exit(1);
    }
}

void ServerManager::SendJsonToServer(const json& j) {
    string json_data = JsonToString(j); // string으로 변환
    string request = "POST / HTTP/1.1\r\n" +
            "Host: 127.0.0.1:8080\r\n" +
            "Content-Type: application/json\r\n" + 
            "Content-Length: " + to_string(json_data.length()) + "\r\n" + 
            "\r\n" + json_data;

    // 5. 서버에 요청 전송
    send(sock, request.c_str(), request.length(), 0);
    cout << "JSON data sent to server" << endl;
}

string ServerManager::ReceiveDataFromServer() {
    char buffer[BUFFER_SIZE];
    // 서버 응답 수신
    int valRead = read(sock, &buffer[0], BUFFER_SIZE);
    if (valRead > 0) {
        cout << "Server response: \n" << buffer << endl;
    } 
    else {
        cerr << "Failed to receive response from server" << endl;
    }
    return buffer;
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
    struct select selection = sandwich.GetSelected();

    short bitTopping = 0;
    short bitVegetable = 0;
    short bitSauce = 0;

    j.at("Main Sandwich").get_to(selection.menu);
    j.at("Is 15cm?").get_to(selection.is15);
    j.at("Bread").get_to(selection.bread);
    j.at("Topping").get_to(selection.topping);
    j.at("Cheese").get_to(selection.cheese);
    j.at("Vegetable").get_to(selection.vegetable);
    j.at("Sauce").get_to(selection.sauce);
    j.at("Is Set").get_to(selection.isSet);
    j.at("Cookie").get_to(selection.cookie);
    j.at("Drink").get_to(selection.drink);
    j.at("Chips").get_to(selection.chips);
}

void ServerManager::SendCartToServer(const Cart& cart) {
    json jSandwich = cart.GetSandwiches();
    json jChips;
    json jCookie;
    json drinks;
    json jTotal;
    SendJsonToServer(jTotal);
}