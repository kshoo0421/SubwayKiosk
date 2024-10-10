#include "Sandwich.h"

//샌드위치 메뉴명 선택
void Sandwich::SelectMenu(MainSandwich m)
{
    selection.menu = m;
}

 //길이 선택(15cm or 30cm)
void Sandwich::SelectSize(bool b)
{
    selection.is15 = b;
}

//빵 선택
void Sandwich::SelectBread(Bread b)
{
    selection.bread=b;
}

//추가 재료 선택
void Sandwich::SelectTopping(bool t[])
{
    for (int i = 0; i < 7; i++) {
        selection.topping[i] = t[i];
    }
}

//치즈 선택
void Sandwich::SelectCheese(Cheese c)
{
    selection.cheese=c;
}

 //야채 선택
void Sandwich::SelectVegetable(bool v[])
{
    for(int i = 0;i<8;i++)
    {
        selection.vegetable[i] = v[i];
    }
}

//소스 선택
void Sandwich::SelectSauce(bool s[])
{
    for(int i = 0;i<14;i++)
    {
        selection.sauce[i] = s[i];
    }
}

//세트 여부 선택
void Sandwich::SelectSet(bool b)
{
    selection.isSet=b;
}

 //쿠키 선택
void Sandwich::SelectCookie(Cookie c)
{
   selection.cookie=c;
}

//음료 선택
void Sandwich::SelectDrink(Drink d)
{
    selection.drink=d;
}

//칩 선택
void Sandwich::SelectChips(Chips c)
{
    selection.chips=c;
}

select Sandwich::GetSelected() const
{
    return selection;
}
