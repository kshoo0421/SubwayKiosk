#ifndef ENUM_H
#define ENUM_H

/* 메인 샌드위치 메뉴명 */
enum class MainSandwich : int {
    EggMayo     = 0,    // 에그마요
    Ham         = 1,    // 햄
    Tuna        = 2,    // 참치
    BLT         = 3,    // B.L.T
    ItalianBMT  = 4,    // 이탈리안 B.M.T

    Veggie              = 5,    // 배지
    ChickenSlice        = 6,    // 치킨 슬라이스
    SubwayClub          = 7,    // 써브웨이 클럽
    RotiserieBBQChicken = 8,    // 로티세리 바비큐 치킨
    RoastedChicken        = 9,    // 로스트 치킨

    ChickenTeriyaki   = 10,   // 치킨 데리야끼
    SpicyItalian        = 11,   // 스파이시 이탈리안
    PulledPorkBBQ       = 12,   // 풀드포크 바비큐
    Staek_Cheese        = 13,   // 스테이크 & 치즈
    ChickenBaconAvocado = 14,   // 치킨 베이컨 아보카도
    Shrimp              = 15,   // 쉬림프    
    KBBQ                = 16,   // K-바비큐

    SpicyShrimp             = 17,   // 스파이시 쉬림프
    Lobster                 = 18,   // 랍스터
    HalfLobster_HalfShrimp  = 19,   // 하프 랍스터 & 하프 쉬림프
    Beef_Mushroom    = 20,   // 안창 비프 & 머쉬룸
    Beef             = 21    // 안창 비프
};

/* 빵 종류 */
enum class Bread : int {
    Wheat = 0,              // 위트
    HoneyOat = 1,           // 허니 오트
    White = 2,              // 화이트
    HeartyItalian = 3,      // 하티 이탈리안
    ParmesanOregano = 4,    // 파마산 오레가노
    Flatbread = 5           // 플랫 브레드
};

/* 추가 재료 */
enum class Topping : int {
    Shrimp = 0,     // 새우
    EggMayo = 1,    // 에그마요
    Omelet = 2,     // 오믈렛
    Avocado = 3,    // 아보카도
    Pepperoni = 4,  // 페퍼로니
    Bacon = 5,      // 베이컨
    DoubleMeat = 6  // 더블 미트
};

/* 치즈 */
enum class Cheese : int {
    AmericanCheese = 0,     // 아메리칸 치즈
    ShredCheese = 1,        // 슈레드 치즈
    MozzarellaCheese = 2    // 모짜렐라 치즈
};

/* 야채 */
enum class Vegetable : int{
    Cabbage = 0,    // 양배추
    Cucumber = 1,   // 오이
    Tomato = 2,     // 토마토
    Onion = 3,      // 양파
    Pimento = 4,    // 피망
    Pickle = 5,     // 피클
    Jalapeno = 6,   // 할라피뇨
    Olive = 7       // 올리브
};

/* 소스 */ 
enum class Sauce : int {
    Mayonnaise = 0,     // 마요네즈
    Ranch = 1,          // 렌치

    Mustard = 2,            // 머스타드
    Horseradish = 3,        // 홀스 레디시
    SouthwestChipotle = 4,  // 사우트웨스트치폴레
    HotChili = 5,           // 핫칠리

SmokeBBQ = 6,           // 스모크바비큐
    SweetChili = 7,     // 스위트칠리
    HoneyMustard = 8,   // 허니머스타드
    SweetOnion = 9,     // 스위트어니언

    Salt = 10,          // 소금
    Pepper = 11,        // 후추
    OliveOil = 12,      // 올리브오일
    RedwineVinegar = 13 // 레드와인식초
};

/* 쿠키 */
enum class Cookie : int { 
    OatmealRaisin = 0,          // 오트밀레이즌
    WhiteChocoMacadamia = 1,    // 화이트 초코 마카다미아
    RasberryCheeseCake = 2,     // 라즈베리치즈케이크
    ChocoChip = 3,              // 초코칩
    DoubleChocoChip = 4         // 더블초코칩
};
#endif // ENUM_H
