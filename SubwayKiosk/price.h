#ifndef PRICE_H
#define PRICE_H
#include "Singleton.h"
#include "enum.h"

class Price : public Singleton<Price> {
    friend class Singleton<Price>;
private:
    Price(); // 생성자는 private로 설정

    int price15[22];    // 15cm 가격
    int price30[22];    // 30cm 가격
    int toppingPrice[7]; // 추가 토핑 가격

    void InitPrices();
public:
    int GetSandwichPrice(MainSandwich option, bool is15);
};
#endif