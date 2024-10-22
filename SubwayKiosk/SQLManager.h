#ifndef SQL_MAANGER_H
#define SQL_MAANGER_H
#include "Singleton.h"
#include "enum.h"
#include <QtSql>
#include <QString>

class SQLManager : public Singleton<SQLManager> {
    friend class Singleton<SQLManager>;
private:
        struct Price{
           int _15cm;
           int _30cm;
       };
        struct Detail{
            QString nameEn; //샌드위치 영문명
            QString nameKr; //샌드위치 한글명
            int kcal; //열량
            float protein; //단백질(g)
            float saturatedFatty; //포화지방(g)
            float sugar; //당류(g)
            int natrium; //나트륨(mg)
            QString expln; //메뉴 설명
        };

        static QList<Price> priceList; //가격  리스트
        QList<Detail> detailList; //메뉴 상세 정보 리스트
        QList<QString> breadList; //빵 리스트
        QList<QString> toppingList; //토핑 리스트
        QList<QString> cheeseList; //치즈 리스트
        QList<QString> vegetableList; //야채 리스트
        QList<QString> sauceList; //소스 리스트
        QList<QString> cookieList; //쿠키 리스트
        QList<QString> drinkList; //음료 리스트
        QList<QString> chipsList; //감자칩

        SQLManager();

public:
        static SQLManager* getInstance() {
            static SQLManager instance;
            return &instance;
        }

    static int GetSandwichPrice(MainSandwich option, bool is15, bool isSet); //샌드위치 가격 반환
    Detail GetDetail(MainSandwich option); //샌드위치 상세 정보 반환
    QList<QString> GetBreadList(); //빵 정보 반환
    QList<QString> GetToppingList(); //토핑 정보 반환
     QList<QString> GetCheeseList(); //치즈 정보 반환
     QList<QString> GetVegetableList(); //야채 정보 반환
      QList<QString> GetSauceList(); //소스 정보 반환
     QList<QString> GetCookieList(); //쿠키 정보 반환
      QList<QString> GetDrinkList(); //음료 정보 반환
     QList<QString> GetChipsList(); //감자칩 정보 반환
};
#endif
