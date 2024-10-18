#include "subwaykiosk.h"
#include "./ui_subwaykiosk.h"
#include <QScrollArea>
#include <QLabel>

SubwayKiosk::SubwayKiosk(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SubwayKiosk)
{
    ui->setupUi(this);

/* 메뉴 폰트 변경*/
    setMenuTextStyle();

}

SubwayKiosk::~SubwayKiosk()
{
    delete ui;
}


void SubwayKiosk::setMenuTextStyle()
{
    //1. 클래식
    ui->textEggMayo->setStyleSheet( "QLabel { font:bold; font-size:16px; }");
    ui->testHam->setStyleSheet("QLabel { font : bold; font-size:16px; }");
    ui->textTuna->setStyleSheet("QLabel { font : bold;font-size:16px; }");
    ui->textBLT->setStyleSheet( "QLabel { font:bold; font-size:16px; }");
    ui->textItalian->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    //2. 프레시 앤 라이트
    ui->textVeggie->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textChickenSlice->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textSubwayClub->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textRotisserie->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textRoasted->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    //3. 프리미엄
    ui->textTeriyaki->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textSpicy->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textPulled->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textSteak->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textAvocado->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textShrimp->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textKBBQ->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    //4. 신제품/기간한정 메뉴
    ui->textSpicyShrimp->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textLobster->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textHalfLob->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textBeef_Mush->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
    ui->textBeef->setStyleSheet( "QLabel { font:bold;font-size:16px; }");
}
