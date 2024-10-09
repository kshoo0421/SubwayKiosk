#include "ServerManager.h"

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