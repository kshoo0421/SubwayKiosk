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
    qDebug()<<db.driver();
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
            info.nameEn = query.value(0).toString(); //첫 번째 칼럼 : 영문명
            info.nameKr = query.value(1).toString(); // 첫 번째 칼럼 : 한글명
            info.kcal = query.value(2).toInt();  // 두 번째 칼럼: 열량
            info.protein = query.value(3).toFloat();  // 세 번째 칼럼: 단백질
            info.saturatedFatty=query.value(4).toFloat(); // 네 번째 칼럼: 포화 지방
            info.sugar=query.value(5).toFloat(); // 다섯 번째 칼럼: 당류
            info.natrium = query.value(6).toInt(); // 여섯 번째 칼럼: 나트륨
            info.expln = query.value(7).toString(); // 일곱 번째 칼럼: 상세 설명
            detailList.append(info);  // 리스트에 추가
        }
    } else {
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }
    /* 리스트에 빵 정보 저장 */
    if(query.exec("SELECT * FROM Bread")){
        while(query.next())
        {
            breadList.append(query.value(0).toString());
        }
    }
    else{
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }
    /* 리스트에 토핑 정보 저장 */
    if(query.exec("SELECT * FROM Topping")){
        while(query.next())
        {
            toppingList.append(query.value(0).toString());
        }
    }
    else{
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }
    /* 리스트에 치즈 정보 저장 */
    if(query.exec("SELECT * FROM Cheese")){
        while(query.next())
        {
            cheeseList.append(query.value(0).toString());
        }
    }
    else{
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }
    /* 리스트에 야채 정보 저장 */
    if(query.exec("SELECT * FROM Vegetable")){
        while(query.next())
        {
            vegetableList.append(query.value(0).toString());
        }
    }
    else{
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }
    /* 리스트에 소스 정보 저장 */
    if(query.exec("SELECT * FROM Sauce")){
        while(query.next())
        {
            sauceList.append(query.value(0).toString());
        }
    }
    else{
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }
    /* 리스트에 쿠키 정보 저장 */
    if(query.exec("SELECT * FROM Cookie")){
        while(query.next())
        {
            cookieList.append(query.value(0).toString());
        }
    }
    else{
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }
    /* 리스트에 음료 정보 저장 */
    if(query.exec("SELECT * FROM Drink")){
        while(query.next())
        {
            drinkList.append(query.value(0).toString());
        }
    }
    else{
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }
    /* 리스트에 감자칩 정보 저장 */
    if(query.exec("SELECT * FROM Chips")){
        while(query.next())
        {
            chipsList.append(query.value(0).toString());
        }
    }
    else{
        qDebug() << "Query execution failed: " << query.lastError().text();
        return ;
    }

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

QList<QString> SQLManager::GetBreadList(){    return breadList;} //빵 이름 리스트 반환
QList<QString> SQLManager::GetToppingList(){    return toppingList; }//토핑 이름 리스트 반환
QList<QString> SQLManager::GetCheeseList(){return cheeseList;} //치즈 정보 반환
QList<QString> SQLManager::GetVegetableList(){return vegetableList;} //야채 정보 반환
QList<QString> SQLManager::GetSauceList(){return sauceList;} //소스 정보 반환
QList<QString> SQLManager::GetCookieList(){return cookieList;} //쿠키 정보 반환
QList<QString> SQLManager::GetDrinkList(){return drinkList;} //음료 정보 반환
QList<QString> SQLManager::GetChipsList(){return chipsList;} //감자칩 정보 반환
