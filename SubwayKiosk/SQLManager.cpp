#include"SQLManager.h"
#include <QtSql>
#include <QDebug>
#include <QString>
using namespace std;

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
    if (!query.exec("SELECT * FROM Price")) {
        qDebug() << "Price query execution failed: " << query.lastError().text();
    } else {
        while (query.next()) {
            // Price 테이블에서 데이터를 처리
            int price15cm = query.value(0).toInt(); // 15cm 가격
            int price30cm = query.value(1).toInt(); // 30cm 가격
            qDebug() << "15cm Price:" << price15cm << ", 30cm Price:" << price30cm;
        }
    }

    if (!query.exec("SELECT * FROM Detail")) {
        qDebug() << "Details query execution failed: " << query.lastError().text();
    } else {
        while (query.next()) {
            int kcal = query.value(0).toInt();
            float protein = query.value(1).toFloat();
            float satFat = query.value(2).toFloat();
            float sugar = query.value(3).toFloat();
            int nat = query.value(4).toInt();
            QString expln = query.value(5).toString();
            qDebug()<<"열량 : "<<kcal<<"kcal, 단백질 = "<<protein<<"g, 포화지방 : "<<satFat<<", 당류 : "<<sugar<<", 상세 설명 : "<<expln;
        }
    }

}
