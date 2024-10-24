#include "ServerFunction.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

static int server_fd;
static struct sockaddr_in address;
static int opt = 1;
static int addrlen;
static vector<thread> threads;

/* 1. 서버 데몬화 */
void Daemonize() {
    // 1. 부모 프로세스 종료하여 자식 프로세스를 고아 프로세스로 만듦
    pid_t pid = fork();
    if (pid < 0) {
        // fork 실패
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        // 부모 프로세스 종료
        exit(EXIT_SUCCESS);
    }

    // 2. 새 세션 생성
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    // 3. 두 번째 fork 호출하여 세션 리더가 되지 않도록 함
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // 4. 파일 권한 마스크 설정
    umask(0);

    // 5. 루트 디렉터리로 변경
    chdir("/");

    // 6. 불필요한 파일 디스크립터 닫기
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // 7. 표준 입출력 재설정 (로그용 파일)
    int fd = open("/tmp/daemon_server.log", O_RDWR | O_CREAT | O_APPEND, 0600);
    if (fd < 0) {
        exit(EXIT_FAILURE);
    }
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
}

/* 2. 소켓 생성 */
void MakeSocket() {
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
}

/* 3. 소켓 옵션 설정 */
void SetSocketOption() {
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}

/* 4. 주소 설정 및 바인딩 */
void BindAddress() {
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

/* 5. 클라이언트 대기 상태 설정 */
void SetWaitingMode() {
    if (listen(server_fd, 10) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }
}

/* 6. 서버 운영 */
void ServerService() {
    cout << "서버 운영 시작" << endl;
    addrlen = sizeof(address);

    while (true) {
        int new_socket;
        // 6-(1) 클라이언트 연결 수락
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept");
            exit(EXIT_FAILURE);
        }
        cout << "수락 완료" << endl;

        // 6-(2) 새 스레드에서 클라이언트 요청 처리
        threads.emplace_back(thread(HandleClient, new_socket));
    }
}

/* 6-(2) 클라이언트 요청 처리 */
void HandleClient(int clientSocket) {
    static int curIdx = 101;
    char buffer[3000];
    read(clientSocket, buffer, 30000);
    cout << "Client request: \n" << buffer << endl;

    // HTTP 요청에서 본문 추출
    string request(buffer);
    size_t contentPos = request.find("\r\n\r\n");
    string body = "";
    if (contentPos != string::npos) {
        body = request.substr(contentPos + 4);
    }

    // 받은 JSON 데이터 출력
    cout << "Received JSON data: " << body << endl;

    // JSON 데이터를 파일에 저장
    string fileName = "cart_" + to_string(curIdx) + ".json";
    ofstream jsonFile("/home/pi/SubwayKiosk/Data/" + fileName);
    if (jsonFile.is_open()) {
        jsonFile << body;
        jsonFile.close();
        cout << "JSON data saved to /home/pi/SubwayKiosk/Data/" << fileName << endl;
    } 
    else {
        cerr << "Failed to open file for writing" << endl;
    }
    // JSON 응답 생성
    json j = json{{"message", "Data received successfully"},
        {"status", "OK"}, {"waiting number", curIdx}, {"Type", "response"}};
    string responseBody = j.dump();

    // HTTP 응답 생성
    ostringstream response;
    response << "HTTP/1.1 200 OK\n" << "Content-Type: application/json\n"
        << "Content-Length: " << responseBody.length() << "\n\n"
        << responseBody;

    // 응답 전송
    write(clientSocket, response.str().c_str(), response.str().length());

    curIdx++;
    // 소켓 닫기
    close(clientSocket);
}

/* 7. 모든 스레드 종료 대기 */
void WaitForThreadEnd() {
    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}