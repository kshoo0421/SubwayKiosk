#ifndef SERVER_MANGER_H
#define SERVER_MANGER_H

#include <string>
#include "Singleton.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

// json 변환 테스트용 구조체
typedef struct tmp {
    bool b1;
    int i1;
    int i2;
    float f1;
} TMP;

class ServerManager : public Singleton<ServerManager> {
    friend class Singleton<ServerManager>;
private:
    ServerManager();
    json Tmp2Json(const TMP& tmp);
    TMP Json2Tmp(const json& j);
public:
    // 장바구니 데이터 보내기
    // 대기번호 데이터 받기
    // 장바구니 데이터 받기
};


#endif