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
#include <QTableWidget>
#include <QHeaderView>
#include <QButtonGroup>
#include <QRadioButton>
#include "ServerManager.h"
#include "DatabaseManager.h"

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
    applyBtnStyle(4, 0); // 초기 설정 (-1 : 선택된 버튼 없음)
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


    modal->setFixedSize(QSize(600,400));

    SQLManager *sql =  SQLManager::getInstance(); //sql 저장 정보 가져오기

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

            //성분표
            QTableWidget *table = new QTableWidget;
            for(int i = 0;i<5;i++)
                table->insertColumn(i);
            QStringList header;
            header<<"열량(kcal)"<<"단백질(g)"<<"포화지방(g)"<<"당류(g)"<<"나트륨(mg)";
            table->setHorizontalHeaderLabels(header);

            QStringList content;
            content <<QString::number(sql->GetDetail(sandwichType).kcal)<<QString::number(sql->GetDetail(sandwichType).protein)<<QString::number(sql->GetDetail(sandwichType).saturatedFatty)<<QString::number(sql->GetDetail(sandwichType).sugar)<<QString::number(sql->GetDetail(sandwichType).natrium);
            table->insertRow(0);
            for(int j = 0; j < 5; j++)
            {
                QTableWidgetItem* item = new QTableWidgetItem(content[j]);
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                table->setItem(0,j, item);
            }

            table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //가로 너비에 맞추기
            table->setFixedHeight(55); //세로 크기 고정
            table->verticalHeader()->setVisible(false); //row 앞 헤더 삭제

            QLabel *info = new QLabel("상세설명");
            info->setStyleSheet("font : bold;");
            QLabel *expln = new QLabel(sql->GetDetail(sandwichType).expln); // 상세 설명

            title->setAlignment(Qt::AlignCenter); // 이름 가운데 정렬
            title->setStyleSheet("font : bold; font-size: 16px;"); //이름 스타일 설정

            imageLabel->setAlignment(Qt::AlignCenter); //이미지 가운데 정렬

            //  expln->setWordWrap(true); //자동 줄 바꿈
            // expln->setMaximumWidth(350); // 최대 너비 설정

            QPushButton *btnCancel = new QPushButton; //취소 버튼
            btnCancel->setText("취소하기");
            btnCancel->setStyleSheet("font : bold;");
            btnCancel->setFixedSize(QSize(100,35));
            connect(btnCancel,SIGNAL(clicked()),this,SLOT(closeModal())); //모달 종료

            QPushButton *btnOrder = new QPushButton; //주문 버튼
            btnOrder->setText("주문하기");
            btnOrder->setStyleSheet("background-color : green; color : white; font:bold;");
            btnOrder->setFixedSize(QSize(100,35));
            connect(btnOrder,SIGNAL(clicked()),this, SLOT(selectOrder()));
            // connect(btnOrder,SIGNAL(clicked()), this, SLOT(SihooTest()));

            // 버튼 가로 배치할 레이아웃
            QHBoxLayout *layout = new QHBoxLayout;
            layout->addWidget(btnCancel);  // 취소 버튼 추가
            layout->addWidget(btnOrder);  // 주문 버튼 추가

            modalLayout->addWidget(imageLabel); //모달에 이미지 추가
            modalLayout->addWidget(title); // 모달에 샌드위치 이름 추가
            modalLayout->addWidget(table); //성분표 추가
            modalLayout->addWidget(info); //"상세설명" 타이틀 추가
            modalLayout->addWidget(expln); // 모달에 상세 설명 추가
            modalLayout->addLayout(layout); // 버튼 레이아웃 추가

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


void SubwayKiosk::closeModal() //모달 종료(취소 버튼)
{
    modal->close();
}

void SubwayKiosk::selectOrder() //재료 선택(주문 버튼)
{
    modal->close();
    //위젯 추가해서 위에 쌓기

    QStackedWidget *orderWidget = new QStackedWidget;

    QWidget* sizeWidget = selectSize(); //사이즈 선택 위젯 생성


    orderWidget->addWidget(sizeWidget);

    // 주문 모달 생성
    QDialog *orderModal = new QDialog;
    orderModal->setFixedSize(QSize(500,400));
    orderModal->setStyleSheet("background-color : white;");
    orderModal->setLayout(new QVBoxLayout); // 새로운 레이아웃 설정 (모달이 이미 열려있어야 함)
    orderModal->layout()->addWidget(orderWidget);
    orderModal->show();

}

QWidget* SubwayKiosk::selectSize()
{
    /* 사이즈 선택 */
    QWidget *sizeWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *sizeLayout = new QVBoxLayout(sizeWidget); //수직 레이아웃 생성

    QPushButton *prev = new QPushButton; //이전 버튼
    QPushButton *next = new QPushButton; //다음 버튼
    prev->setText(QString("이전"));
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(prev);  // 취소 버튼 추가
    layout->addWidget(next);  // 주문 버튼 추가


    QLabel* title = new QLabel("사이즈 선택");
    title->setStyleSheet("font : bold; font-size : 20px;");
    // title->setAlignment(Qt::AlignTop);

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정


    QRadioButton *option[2];
    option[0] = new QRadioButton("15cm", this);
    option[1] = new QRadioButton("30cm", this);
    option[0]->setStyleSheet("font-size : 20px;");
    option[1]->setStyleSheet("font-size : 20px;");

    QButtonGroup *btnGroup = new QButtonGroup(this);
    btnGroup->addButton(option[0]);
    btnGroup->addButton(option[1]);

    sizeLayout->addWidget(title);
    sizeLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    sizeLayout->addWidget(option[0]);
    sizeLayout->addWidget(option[1]);
    sizeLayout->addLayout(layout);

    // 버튼 가운데 정렬
    sizeLayout->setAlignment(option[0], Qt::AlignCenter);
    sizeLayout->setAlignment(option[1], Qt::AlignCenter);

    return sizeWidget;
}

//#include "ServerManager.h"
#include "enum.h"

void SubwayKiosk::SihooTest() {
    DatabaseManager& dataManager = DatabaseManager::Instance();
    //ServerManager& serverManager = ServerManager::Instance();

    Cart testCart = Cart();

    Sandwich sandwich = Sandwich();
    struct select tmpSel;

    tmpSel.bread = Bread::Flatbread;
    tmpSel.cheese = Cheese::AmericanCheese;
    tmpSel.chips = Chips::Nacho;
    tmpSel.cookie = Cookie::ChocoChip;
    tmpSel.drink = Drink::Coke;
    tmpSel.is15 = true;
    tmpSel.isSet = false;
    tmpSel.menu = MainSandwich::BLT;
    tmpSel.sauce[(int)Sauce::HoneyMustard] = true;
    tmpSel.sauce[(int)Sauce::Pepper] = true;
    tmpSel.sauce[(int)Sauce::Ranch] = true;
    tmpSel.topping[(int)Topping::Bacon] = true;
    tmpSel.vegetable[(int)Vegetable::Olive] = true;
    tmpSel.vegetable[(int)Vegetable::Cabbage] = true;

    testCart.sandwich.emplace_back(sandwich);
    testCart.chips.emplace_back(Chips::OhPotato);
    testCart.drinks.emplace_back(Drink::Cider);
    testCart.cookie.emplace_back(Cookie::ChocoChip);

    qDebug() << dataManager.serverManager.CartToJsonString(testCart);
    dataManager.serverManager.SendCartToServer(testCart);
}
