#ifndef SERVER_MANGER_H
#define SERVER_MANGER_H

#define SERVER_ADDR "127.0.0.1"
#define BUFFER_SIZE 3000

#include <string>
#include "Singleton.h"
#include "json.hpp"
#include "Cart.h"

using namespace std;
using json = nlohmann::json;

class ServerManager : public Singleton<ServerManager> {
    friend class Singleton<ServerManager>;
private:
    int sock = 0;
    struct sockaddr_in servAddr;

    ServerManager();
    ~ServerManager();
    void ConnectToServer();

    void SendJsonToServer(const json& j);   // 서버로 json 데이터 송신
    char* ReceiveDataFromServer();         // 서버로부터 string 데이터 수신

    // 이미 json 형식인 string을 json 구조체로 변환
    json StringToJson(const string& s) { return json::parse(s); } 
    // json을 string 형식으로 변환
    string JsonToString(const json& j) { return j.dump(); }

public:
    void SendCartToServer(const Cart& cart);
    // 장바구니 데이터 보내기
    // 대기번호 데이터 받기
    // 장바구니 데이터 받기
};
#endif
