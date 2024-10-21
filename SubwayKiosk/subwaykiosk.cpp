#include "subwaykiosk.h"
#include "./ui_subwaykiosk.h"
#include <QScrollArea>
#include <QDebug>
#include <QIcon>
#include <QDialog>
#include <QSize>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include "SQLManager.h"
#include "ManageFrame.h"
#include <QPixmap>

SubwayKiosk::SubwayKiosk(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SubwayKiosk)
{
    ui->setupUi(this);

    /* 버튼 카테고리 */
    QPushButton *btnCategories[] = {
        ui->btnSandwich, ui->btnCookie, ui->btnChip, ui->btnDrink,
    };

    // 스타일 기본 설정
    applyBtnStyle( 4, 0); // 초기 설정 (-1 : 선택된 버튼 없음)
    setMenuTextStyle(); // 메뉴 텍스트 스타일 설정

    // 카트 이미지 넣음
    ui->btnCart->setIcon(QIcon(":/Resources/cart.png"));

    /* 버튼 클릭 시 페이지 이동 */  
    for (int i = 0; i < 4; ++i) {
        connect(btnCategories[i], &QPushButton::clicked, [=]() {
            ui->selectMenuWidget->setCurrentIndex(i);
            applyBtnStyle(4, i); // 선택된 버튼 스타일 적용
        });
    }

    ManageFrame *frameCategories[] = {
        ui->frameEggMayo, ui->frameHam, ui->frameTuna, ui->frameBLT, ui->frameBMT,
    };
    /* 메뉴 선택 시 연결 창 */
    QDialog *modal = new QDialog(this);
    QVBoxLayout *modalLayout = new QVBoxLayout(modal); //모달 담을 레이아웃
    modal->setFixedSize(QSize(400,400));

    SQLManager *sql =  SQLManager::getInstance();

    // 클릭한 프레임에 해당하는 enum을 사용해 SQL에서 정보를 가져와서 출력
    for (int i = 0; i < 5; ++i) {
        MainSandwich sandwichType = static_cast<MainSandwich>(i); // enum 값으로 변환

        connect(frameCategories[i], &ManageFrame::frameClicked, [=](){

            while (QLayoutItem* item = modalLayout->takeAt(0)) { // 모달 초기화
                delete item->widget();  // 위젯 제거
                delete item;  // 레이아웃 아이템 제거
            }

            // 클릭한 프레임의 이미지 가져오기
            QPixmap image = frameCategories[i]->getImage(i);  // 프레임에 있는 이미지 가져오는 함수 (가정)
            QLabel *imageLabel = new QLabel();
            imageLabel->setPixmap(image.scaled(200, 200, Qt::KeepAspectRatio)); // 이미지 크기 조정 (원하는 크기로 설정)

            QLabel *title = new QLabel(sql->GetDetail(sandwichType).name); // 샌드위치 이름
            QLabel *expln = new QLabel(sql->GetDetail(sandwichType).expln); // 상세 설명

            title->setAlignment(Qt::AlignCenter); // 가운데 정렬
            title->setStyleSheet("font : bold; font-size: 16px;");
            imageLabel->setAlignment(Qt::AlignCenter);
            expln->setAlignment(Qt::AlignCenter);
          //  title->setWordWrap(true);
            expln->setWordWrap(true);
            expln->setMaximumWidth(350); // 최대 너비 설정

             modalLayout->addWidget(imageLabel); //모달에 이미지 추가
            modalLayout->addWidget(title); // 모달에 샌드위치 이름 추가
            modalLayout->addWidget(expln); // 모달에 상세 설명 추가

            modal->exec(); // 모달 실행
        });
    }

}

SubwayKiosk::~SubwayKiosk()
{
    delete ui;
}

void SubwayKiosk::applyBtnStyle( int size, int selectedIdx)
{

    /* 버튼 카테고리 */
    QPushButton *btnCategories[] = {
        ui->btnSandwich, ui->btnCookie, ui->btnChip, ui->btnDrink,
    };
    for (int i = 0; i < size; ++i) {
        if (i == selectedIdx) {
            // 선택된 버튼 스타일
            btnCategories[i]->setStyleSheet(
                " border: none; font: bold; font-size: 20px; background-color: gray; "
                );
        } else {
            // 기본 버튼 스타일
            btnCategories[i]->setStyleSheet(
                " border: none; font: bold; font-size: 20px; "
                );
        }
    }
}

void SubwayKiosk::applyLabelStyle(QLabel *labels[], int size)
{
    for (int i = 0; i < size; ++i) {
        labels[i]->setStyleSheet(" font: bold; font-size: 16px; ");
    }
}

void SubwayKiosk::setMenuTextStyle()
{
    QLabel *sandwichLabels[] = {
        ui->textEggMayo, ui->textHam, ui->textTuna, ui->textBLT, ui->textItalian, //1. 클래식
        ui->textVeggie, ui->textChickenSlice, ui->textSubwayClub, ui->textRotisserie, ui->textRoasted, //2. 프레시 앤 라이트
        ui->textTeriyaki, ui->textSpicy, ui->textPulled, ui->textSteak, ui->textAvocado, ui->textShrimp, ui->textKBBQ, //3. 프리미엄
        ui->textSpicyShrimp, ui->textLobster, ui->textHalfLob, ui->textBeef_Mush, ui->textBeef, //4. 신제품/기간한정 메뉴
    };

    QLabel *cookieLabels[] = {
        ui->textOatmeal, ui->textWhiteChoco, ui->textRasp, ui->textChoco, ui->textDouble,
    };

    QLabel *chipLabels[] = {
        ui->textPoka, ui->textSwing, ui->textNacho, ui->textOhGam,
    };

    QLabel *drinkLabels[] = {
        ui->textCoke, ui->textSprite, ui->textFanta,
    };

    // 라벨 스타일 적용
    applyLabelStyle(sandwichLabels, sizeof(sandwichLabels) / sizeof(sandwichLabels[0]));
    applyLabelStyle(cookieLabels, sizeof(cookieLabels) / sizeof(cookieLabels[0]));
    applyLabelStyle(chipLabels, sizeof(chipLabels) / sizeof(chipLabels[0]));
    applyLabelStyle(drinkLabels, sizeof(drinkLabels) / sizeof(drinkLabels[0]));
}
