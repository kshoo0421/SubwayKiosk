#ifndef PRICE_H
#define PRICE_H
#include "Singleton.h"

class Price : public Singleton<Price> {
    friend class Singleton<Price>;
private:
    Price(); // 생성자는 private로 설정

    int price15[22];    // 15cm 가격
    int price30[22];    // 30cm 가격

    void InitPrices();
public:
    int GetPrice(class MainSandwich option, bool is15);
};
#endif