#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ServerManager.h"

using namespace std;

void daemonize() {
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

void handle_client(int client_socket) {
    char buffer[30000] = {0};
    read(client_socket, buffer, 30000);
    cout << "Client request: \n" << buffer << endl;

    // HTTP 요청에서 본문 추출
    string request(buffer);
    size_t content_pos = request.find("\r\n\r\n");
    string body = "";
    if (content_pos != string::npos) {
        body = request.substr(content_pos + 4);
    }

    // 받은 JSON 데이터 출력
    cout << "Received JSON data: " << body << endl;

    // JSON 데이터를 파일에 저장
    ofstream json_file("/tmp/received_data.json");
    if (json_file.is_open()) {
        json_file << body;
        json_file.close();
        cout << "JSON data saved to /tmp/received_data.json" << endl;
    } else {
        cerr << "Failed to open file for writing" << endl;
    }

    // JSON 응답 생성
    string response_body = R"({
        "message": "Data received successfully",
        "status": "OK"
    })";

    // HTTP 응답 생성
    ostringstream response;
    response << "HTTP/1.1 200 OK\n" << "Content-Type: application/json\n"
        << "Content-Length: " << response_body.length() << "\n\n"
        << response_body;

    // 응답 전송
    write(client_socket, response.str().c_str(), response.str().length());

    // 소켓 닫기
    close(client_socket);
}

int main() {
    // 서버 데몬화
    daemonize();

    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // 1. 소켓 생성
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. 소켓 옵션 설정
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // 3. 주소 설정 및 바인딩
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 4. 대기 상태로 설정
    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    vector<thread> threads;

    while (true) {
        int new_socket;
        // 5. 클라이언트 연결 수락
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept");
            exit(EXIT_FAILURE);
        }

        // 6. 새 스레드에서 클라이언트 요청 처리
        threads.emplace_back(thread(handle_client, new_socket));
    }

    // 7. 모든 스레드가 종료될 때까지 대기 (사실 서버는 무한 루프라 이 부분은 호출되지 않음)
    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    return 0;
}
