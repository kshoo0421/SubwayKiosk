#include"SQLManager.h"
#include <QDebug>
#include <QList>

using namespace std;


// Static 변수 초기화(클래스 외부에서 초기화 해야 함)
QList<SQLManager::Price> SQLManager::priceList;

SQLManager::SQLManager()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("0000");
    db.setDatabaseName("SandwichInfo");

    if(!db.open())
    {
        qDebug()<<"Database connection failed: "<<db.lastError().text();
        return;
    }
    else{
        qDebug()<<"connected";
    }

     QSqlQuery query;
    /* 리스트에 가격 정보 저장 */
    if (query.exec("SELECT * FROM Price")) {// 쿼리 결과를 QList에 저장
        while (query.next()) {
            Price info;
            info._15cm = query.value(0).toInt();  // 첫 번째 칼럼: 15cm 가격
            info._30cm = query.value(1).toInt();  // 두 번째 칼럼: 30cm 가격
            priceList.append(info);  // 리스트에 추가
        }
    } else {
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }
    /* 리스트에 메뉴 상세 정보 저장 */
    if (query.exec("SELECT * FROM Detail")) {// 쿼리 결과를 QList에 저장
        while (query.next()) {
            Detail info;
            info.name = query.value(0).toString(); // 첫 번째 칼럼 : 이름
            info.kcal = query.value(1).toInt();  // 두 번째 칼럼: 열량
            info.protein = query.value(2).toFloat();  // 세 번째 칼럼: 단백질
            info.saturatedFatty=query.value(3).toFloat(); // 네 번째 칼럼: 포화 지방
            info.sugar=query.value(4).toFloat(); // 다섯 번째 칼럼: 당류
            info.natrium = query.value(5).toInt(); // 여섯 번째 칼럼: 나트륨
            info.expln = query.value(6).toString(); // 일곱 번째 칼럼: 상세 설명
            detailList.append(info);  // 리스트에 추가
        }
    } else {
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }

    // /* DB 정상 로드 확인 */
    // if (!this->query.exec("SELECT * FROM Price")) {
    //     qDebug() << "Price query execution failed: " << this->query.lastError().text();
    // } else {
    //     while (this->query.next()) {
    //         // Price 테이블에서 데이터를 처리
    //         int price15cm = this->query.value(0).toInt(); // 15cm 가격
    //         int price30cm = this->query.value(1).toInt(); // 30cm 가격
    //         qDebug() << "15cm Price:" << price15cm << ", 30cm Price:" << price30cm;
    //     }
    // }

    // if (query.exec("SELECT * FROM Detail")) {
    //     qDebug() << "Details query execution failed: " << query.lastError().text();
    // } else {
    //     while (query.next()) {
    //         int kcal = query.value(0).toInt();
    //         float protein = query.value(1).toFloat();
    //         float satFat = query.value(2).toFloat();
    //         float sugar =query.value(3).toFloat();
    //         int nat = query.value(4).toInt();
    //         QString expln = query.value(5).toString();
    //         qDebug()<<"열량 : "<<kcal<<"kcal, 단백질 = "<<protein<<"g, 포화지방 : "<<satFat<<", 당류 : "<<sugar<<", 상세 설명 : "<<expln;
    //     }
    // }

    db.close();

}

int SQLManager::GetSandwichPrice(MainSandwich option, bool is15, bool isSet)
{
    int index = static_cast<int>(option);
    Price p = priceList.at(index);
    if(is15)
    {
        if(isSet) //15cm 세트
            return p._15cm+2600;
        else //15cm 단품
            return p._15cm;
    }
    else
    {
        if(isSet) //30cm 세트
            return p._30cm+2600;
        else //30cm 단품
            return p._30cm;
    }
}
SQLManager::Detail SQLManager::GetDetail(MainSandwich option)
{
    int index = static_cast<int>(option);
    return this->detailList[index];
}
