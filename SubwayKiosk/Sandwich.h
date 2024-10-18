#ifndef SANDWICH_H
#define SANDWICH_H
#include "enum.h"

struct select{
    //단일 선택 가능 : enum 변수
    //복수 선택 가능 : bool 배열
    MainSandwich menu;
    bool is15;
    Bread bread;
    bool topping[7] = {false,};
    Cheese cheese; //치즈 선택
    bool vegetable[8] = {false,}; //야채 선택
    bool sauce[14] = {false,}; //소스 선택
    bool isSet; //세트 여부
    Cookie cookie; //쿠키 선택
    Drink drink; //음료 선택
    Chips chips; //칩 선택
};

class Sandwich{
private:
    select selection; //선택 정보 저장

public:

    /* 선택 */
    void SelectMenu(MainSandwich m); //메뉴명 선택
    void SelectSize(bool b); //길이 선택(15cm or 30cm)
    void SelectBread(Bread b); //빵 선택
    void SelectTopping(bool t[]); //추가 재료 선택
    void SelectCheese(Cheese c); //치즈 선택
    void SelectVegetable(bool v[]); //야채 선택
    void SelectSauce(bool s[]) ; //소스 선택
    void SelectSet(bool b); //세트 여부 선택
    void SelectCookie(Cookie c); //쿠키 선택
    void SelectDrink(Drink d); //음료 선택
    void SelectChips(Chips c); //칩 선택

    /* 선택 정보 */
    select GetSelected() const;
};

#endif // SANDWICH_H
