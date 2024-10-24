#ifndef SERVER_MANGER_H
#define SERVER_MANGER_H

#define SERVER_ADDR "192.168.0.113"
#define SERVER_PORT 8080
#define BUFFER_SIZE 3000

#include <string>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <QDebug>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")  // 링크 추가
#endif

#include "Singleton.h"
#include "json.hpp"
#include "Cart.h"

using namespace std;
using json = nlohmann::json;

class ServerManager : public Singleton<ServerManager> {
    friend class Singleton<ServerManager>;
private:
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in servAddr;
    vector<char> buffer;

    ServerManager();
    ~ServerManager();
    void ConnectToServer();

    int SendJsonToServer(const json& j);   // 서버로 json 데이터 송신
    string ReceiveDataFromServer();         // 서버로부터 string 데이터 수신

    // 이미 json 형식인 string을 json 구조체로 변환
    json StringToJson(const string& s);
    // json을 string 형식으로 변환
    string JsonToString(const json& j) { return j.dump(); }

public:
    int SendCartToServer(const Cart& cart);
    string CartToJsonString(const Cart& cart);
    void StringToCart(Cart& cart, const string& sJson);
    // 장바구니 데이터 보내기
    // 대기번호 데이터 받기
    // 장바구니 데이터 받기
};
#endif
