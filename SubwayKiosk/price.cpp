#include "price.h"

Price::Price() {
    InitPrices();
}

void Price::InitPrices() {
    price15[(int)MainSandwich::Beef] = 100;

    price30[(int)MainSandwich::Beef] = 100;
    // ...

}

int Price::GetSandwichPrice(MainSandwich option, bool is15) {
    if(is15) return price15[(int)option];
    else return price30[(int)option];
}