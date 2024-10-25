#include "Cart.h"
#include "SQLManager.h"
using namespace std;

Cart::Cart() : totalCnt(0), totalPrice(0) {}

/* 항목 추가 */
void Cart::Add(const Sandwich& sandwich) // 샌드위치 추가
{
    int price;
    select selected = sandwich.GetSelected(); //샌드위치 선택 정보

    this->sandwich.push_back(sandwich);
    totalCnt++;

    price = SQLManager::GetSandwichPrice(selected.menu,selected.is15,selected.isSet);
    totalPrice +=price; // 샌드위치 가격은 Sandwich 객체의 getPrice() 함수로 가져옴
}

void Cart::Add(const Chips& chip) // 칩 추가
{
    this->chips.push_back(chip);
    totalCnt++;
    totalPrice += 1300; // 칩 가격 고정
}

void Cart::Add(const Cookie& cookie) // 쿠키 추가
{
    this->cookie.push_back(cookie);
    totalCnt++;
    totalPrice += 1300; // 쿠키 가격 고정
}

void Cart::Add(const Drink& drink) // 음료 추가
{
    this->drinks.push_back(drink);
    totalCnt++;
    totalPrice += 2500; // 음료 가격 고정
}

/* 항목 삭제 */
void Cart::RemoveSandwich(int index) // 샌드위치 제거
{
    int price; //샌드위치 가격 저장
    select selected;  //샌드위치 선택 정보


    if (index >= 0 && index < sandwich.size()) {
        selected = sandwich[index].GetSelected();
        price = SQLManager::GetSandwichPrice(selected.menu,selected.is15,selected.isSet);
        totalPrice -= price; // 샌드위치 가격 차감
        sandwich.erase(sandwich.begin() + index);
        totalCnt--;
    }
}

void Cart::RemoveChips(int index) // 칩 제거
{
    if (index >= 0 && index < chips.size()) {
        totalPrice -= 1300;
        chips.erase(chips.begin() + index);
        totalCnt--;
    }
}

void Cart::RemoveCookie(int index) // 쿠키 제거
{
    if (index >= 0 && index < cookie.size()) {
        totalPrice -= 1300;
        cookie.erase(cookie.begin() + index);
        totalCnt--;
    }
}

void Cart::RemoveDrink(int index) // 음료 제거
{
    if (index >= 0 && index < drinks.size()) {
        totalPrice -= 2500;
        drinks.erase(drinks.begin() + index);
        totalCnt--;
    }
}

void Cart::clear()
{

    sandwich.clear(); // 샌드위치 저장
    chips.clear(); //칩 저장
    cookie.clear(); //쿠키 저장
    drinks.clear(); //음료 저장
    totalCnt = 0;
    totalPrice = 0; // 총 가격
}

/* 총 가격 계산 */
int Cart::CalculateTotal()
{
    return totalPrice;
}

/* 장바구니 내용 반환 */
vector<Sandwich> Cart::GetSandwiches() const // 샌드위치 목록 반환
{
    return sandwich;
}
vector<Chips> Cart::GetChips() const // 칩 목록 반환
{
    return chips;
}
vector<Cookie> Cart::GetCookies() const // 쿠키 목록 반환
{
    return cookie;
}
vector<Drink> Cart::GetDrinks() const // 음료 목록 반환
{
    return drinks;
}
