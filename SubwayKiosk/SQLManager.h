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
            int kcal; //열량
            float protein; //단백질(g)
            float saturatedFatty; //포화지방(g)
            float sugar; //당류(g)
            int natrium; //나트륨(mg)
            QString expln; //메뉴 설명
        };
        QList<Price> priceList; //가격  리스트
        QList<Detail> detailList; //메뉴 상세 정보 리스트
        SQLManager();
public:
    int GetSandwichPrice(MainSandwich option, bool is15) ; //샌드위치 가격 반환
    SQLManager::Detail GetDetail(MainSandwich option); //샌드위치 상세 정보 반환
};
#endif
