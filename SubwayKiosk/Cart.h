#ifndef CART_H
#define CART_H

#include <vector>
#include "Sandwich.h"

using namespace std;

class Cart {
private:

    // vector<Sandwich> sandwich; // 샌드위치 저장
    // vector<Chips> chips; //칩 저장
    // vector<Cookie> cookie; //쿠키 저장
    // vector<Drink> drinks; //음료 저장
    // int totalCnt;
    // int totalPrice; // 총 가격

public:
    Cart();

    vector<Sandwich> sandwich; // 샌드위치 저장
    vector<Chips> chips; //칩 저장
    vector<Cookie> cookie; //쿠키 저장
    vector<Drink> drinks; //음료 저장
    int totalCnt;
    int totalPrice; // 총 가격

    /* 항목 추가 */
    void Add(const Sandwich& sandwich); // 샌드위치 추가
    void Add(const Chips& chip); //칩 추가
    void Add(const Cookie& cookie); // 쿠키 추가
    void Add(const Drink& drink); //음료 추가

    /* 항목 삭제 */
    void RemoveSandwich(int index); // 샌드위치 제거
    void RemoveChips(int index); //칩 제거
    void RemoveCookie(int index); //쿠키 제거
    void RemoveDrink(int index); //음료 제거

    /* 장바구니 내용 반환 */
    vector<Sandwich> GetSandwiches() const; // 샌드위치 목록 반환
    vector<Chips> GetChips() const; // 칩 목록 반환
    vector<Cookie> GetCookies() const; // 쿠키 목록 반환
    vector<Drink> GetDrinks() const; // 음료 목록 반환

    int CalculateTotal(); // 총 가격 계산 (샌드위치 : priceList(세트는 +2600), 칩/쿠키 : 개당 1300원, 음료 : 2500원)


};

#endif // CART_H
