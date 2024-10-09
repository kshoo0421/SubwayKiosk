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
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // 2. 서버 주소 설정
    if (inet_pton(AF_INET, SERVER_ADDR, &serv_addr.sin_addr) <= 0) {
        cerr << "Invalid address/ Address not supported" << endl;
        return -1;
    }

    // 3. 서버 연결
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Connection Failed" << endl;
        return -1;
    }
    return 0;
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
    // 서버 응답 수신
    int valRead = read(sock, &buffer[0], BUFFER_SIZE);
    if (valRead > 0) {
        cout << "Server response: \n" << buffer << endl;
    } 
    else {
        cerr << "Failed to receive response from server" << endl;
    }
    return buffer.substr(0, valRead);
}


json ServerManager::Tmp2Json(const TMP& tmp) {
    return json{{"i1", tmp.i1}, {"i2", tmp.i2}, {"b1", tmp.b1}, {"f1", tmp.f1}};
}

TMP ServerManager::Json2Tmp(const json& j) {
    TMP tmp;
    j.at("i1").get_to(tmp.i1);
    j.at("i2").get_to(tmp.i2);
    j.at("f1").get_to(tmp.f1);
    j.at("b1").get_to(tmp.b1);
    return tmp;
}

void ServerManager::SendTMPToServer(const TMP& tmp) {
    SendJsonToServer(Tmp2Json(tmp));
}