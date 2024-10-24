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
#include <QPixmap>
#include <QTableWidget>
#include <QHeaderView>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>
#include <QMessageBox>
#include "ServerManager.h"
#include "DatabaseManager.h"
#include "SQLManager.h"
#include "ManageFrame.h"
#include "Cart.h"

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
    ui->labelCart->setStyleSheet("background-color: rgba(255, 255, 255, 0); color : white; font : bold; font-size : 20px;"); //장바구니 제목

    //장바구니 토글 설정
    toggleSandwich = setCartStyle("샌드위치"); toggleSandwich->adjustSize();
    toggleCookie = setCartStyle("쿠키");toggleCookie->setFixedSize(280, 20);
    toggleChips = setCartStyle("칩");toggleChips->setFixedSize(280, 20);
    toggleDrink = setCartStyle("음료");toggleDrink->setFixedSize(280, 20);

    // Sandwich 토글과 그 밑에 항목들을 담을 위젯 생성
    sandwichToggleWidget = new QWidget(this);
    sandwichLayoutToggle = new QVBoxLayout(sandwichToggleWidget);
    sandwichLayoutToggle->setContentsMargins(0, 0, 0, 0);


    // 토글과 항목 레이아웃을 구분하여 설정
    sandwichLayoutToggle->addWidget(toggleSandwich);  // 토글을 레이아웃에 추가

    // Sandwich 항목 추가
    QListWidgetItem *itemSandwich = new QListWidgetItem(ui->cartList);
    ui->cartList->addItem(itemSandwich);
    ui->cartList->setItemWidget(itemSandwich, toggleSandwich);

    // Cookie 항목 추가
    QListWidgetItem *itemCookie = new QListWidgetItem(ui->cartList);
    ui->cartList->addItem(itemCookie);
    ui->cartList->setItemWidget(itemCookie, toggleCookie);

    // Chips 항목 추가
    QListWidgetItem *itemChips = new QListWidgetItem(ui->cartList);
    ui->cartList->addItem(itemChips);
    ui->cartList->setItemWidget(itemChips, toggleChips);

    // Drink 항목 추가
    QListWidgetItem *itemDrink = new QListWidgetItem(ui->cartList);
    ui->cartList->addItem(itemDrink);
    ui->cartList->setItemWidget(itemDrink, toggleDrink);

    ui->btnOrder->setStyleSheet("{ background-color: rgba(255, 255, 255, 0);color:white;  }");
    connect(ui->btnOrder,&QPushButton::clicked,this,[=](){
        vector<Sandwich>  tmp = cart.GetSandwiches();
        for(auto it:tmp)
        {
            qDebug()<<"장바구니 내역"<<static_cast<int>(it.GetSelected().menu);
        }
        int waitNum = dataManager.serverManager.SendCartToServer(cart);
        qDebug()<<"대기번호";
    });

    /* 버튼 클릭 시 페이지 이동 */  
    for (int i = 0; i < 4; ++i) {
        connect(btnCategories[i], &QPushButton::clicked, [=]() {
            ui->selectMenuWidget->setCurrentIndex(i);
            applyBtnStyle(4, i); // 선택된 버튼 스타일 적용
        });
    }

    ManageFrame *frameCategories[] = {
        ui->frameEggMayo, ui->frameHam, ui->frameTuna, ui->frameBLT, ui->frameBMT,
        ui->frameVeggie, ui->frameChickSlice, ui->frameSubwayClub,ui->frameRot,ui->frameRoast,
        ui->frameTeri, ui->frameSpicy, ui->framePulled,ui->frameSteak, ui->frameAvocado, ui->frameShrimp, ui->frameKBBQ,
        ui->frameSpicyShrimp,ui->frameLobster,ui->frameHalf, ui->frameBeefMush,ui->frameBeef,
    };

    /* 샌드위치 메뉴 선택 시 연결 창 */
    modal->setFixedSize(QSize(600,400));

    // 클릭한 프레임에 해당하는 enum을 사용해 SQL에서 정보를 가져와서 출력
    for (int i = 0; i < sizeof(frameCategories)/sizeof(ui->frameAvocado); ++i) {
        MainSandwich sandwichType = static_cast<MainSandwich>(i); // enum 값으로 변환

        //메뉴 클릭 시 이벤트
        connect(frameCategories[i], &ManageFrame::frameClicked, [=](){

            //메뉴 선택 정보 저장
            selected.SelectMenu(sandwichType);

            while (QLayoutItem* item = modalLayout->takeAt(0)) { // 모달 초기화
                delete item->widget();  // 위젯 제거
                delete item;  // 레이아웃 아이템 제거
            }

            // 클릭한 프레임의 이미지 가져오기
            QPixmap image = frameCategories[i]->getImage(i);  // 프레임에 있는 이미지 가져오는 함수 (가정)
            QLabel *imageLabel = new QLabel();
            imageLabel->setPixmap(image.scaled(200, 200, Qt::KeepAspectRatio)); // 이미지 크기 조정 (원하는 크기로 설정)
            QLabel *title = new QLabel(dataManager.sqlManager.GetDetail(sandwichType).nameKr); // 샌드위치 이름

            //성분표
            QTableWidget *table = new QTableWidget;
            for(int i = 0;i<5;i++)
                table->insertColumn(i);
            QStringList header;
            header<<"열량(kcal)"<<"단백질(g)"<<"포화지방(g)"<<"당류(g)"<<"나트륨(mg)";
            table->setHorizontalHeaderLabels(header);

            QStringList content;
            content <<QString::number(dataManager.sqlManager.GetDetail(sandwichType).kcal)<<QString::number(dataManager.sqlManager.GetDetail(sandwichType).protein)<<QString::number(dataManager.sqlManager.GetDetail(sandwichType).saturatedFatty)<<QString::number(dataManager.sqlManager.GetDetail(sandwichType).sugar)<<QString::number(dataManager.sqlManager.GetDetail(sandwichType).natrium);
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
            QLabel *expln = new QLabel(dataManager.sqlManager.GetDetail(sandwichType).expln); // 상세 설명

            title->setAlignment(Qt::AlignCenter); // 이름 가운데 정렬
            title->setStyleSheet("font : bold; font-size: 16px;"); //이름 스타일 설정

            imageLabel->setAlignment(Qt::AlignCenter); //이미지 가운데 정렬

              expln->setWordWrap(true); //자동 줄 바꿈
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

QCheckBox* SubwayKiosk::setCartStyle(QString title) //장바구니 스타일 설정
{
    QCheckBox *toggle = new QCheckBox(title, this);
    toggle->setStyleSheet(
        "QCheckBox::indicator { width: 0px; height: 0px; }" //체크 칸 없애기
        "QCheckBox { height: 20px; color : white; background-color : #e64931; font : bold; }"
        );

    // 화살표 아이콘 설정
    QPixmap pixmap(":/Resources/downArrow.png");
    QPixmap scaledPixmap = pixmap.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    toggle->setIcon(QIcon(scaledPixmap));
    toggle->setIconSize(QSize(20,20));

    return toggle;
}

void SubwayKiosk::closeModal() //모달 종료(취소 버튼)
{
    modal->close();
}

void SubwayKiosk::selectOrder() //재료 선택(주문 버튼)
{
    modal->close();
    //위젯 추가해서 위에 쌓기

    QWidget* sizeWidget = selectSize(); //사이즈 선택 위젯 생성
    QWidget* breadWidget = selectBread(); //빵 선택 위젯 생성
    QWidget* toppingWidget = selectTopping(); //토핑 선택 위젯 생성
    QWidget* cheeseWidget = selectCheese(); //치즈 선택 위젯 생성
    QWidget* vegetableWidget = selectVegetable(); //야채 선택 위젯 생성
    QWidget* sauceWidget = selectSauce(); //야채 선택 위젯 생성
    QWidget* setWidget = selectSet(); //세트 여부 선택 위젯 생성
    QWidget* whichSetWidget = selectWhichSet(); // 세트 종류 선택 위젯 생성
    QWidget* cookieWidget = selectCookie(); //쿠키 선택 위젯 생성
    QWidget* drinkWidget = selectDrink(); //음료 선택 위젯 생성
    QWidget* chipsWidget = selectChips(); //칩 선택 위젯 생성

    orderWidget->addWidget(sizeWidget);
    orderWidget->addWidget(breadWidget);
    orderWidget->addWidget(toppingWidget);
    orderWidget->addWidget(cheeseWidget);
    orderWidget->addWidget(vegetableWidget);
    orderWidget->addWidget(sauceWidget);
    orderWidget->addWidget(setWidget);
    orderWidget->addWidget(whichSetWidget);
    orderWidget->addWidget(cookieWidget);
    orderWidget->addWidget(chipsWidget);
    orderWidget->addWidget(drinkWidget);

    orderWidget->setCurrentIndex(0);

    // 주문 모달 생성
    orderModal = new QDialog;
    connect(orderModal,&QDialog::rejected,this,[=](){ //모달 창 종료 시 StackedWidget 초기화
        orderWidget = new QStackedWidget;
    });
    orderModal->setFixedSize(QSize(500,400));
    orderModal->setStyleSheet("background-color : white;");
    orderModal->setLayout(new QVBoxLayout); // 새로운 레이아웃 설정 (모달이 이미 열려있어야 함)
    orderModal->layout()->addWidget(orderWidget);
    orderModal->show();

}
/* 사이즈 선택 위젯 구성 */
QWidget* SubwayKiosk::selectSize()
{
    /* 사이즈 선택 */
    QWidget *sizeWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *sizeLayout = new QVBoxLayout(sizeWidget); //수직 레이아웃 생성

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

    //다음 버튼
    QPushButton *next = new QPushButton; //다음 버튼
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");
    connect(next,&QPushButton::clicked,this,[this, option]()
    {
        if(!option[0]->isChecked() && !option[1]->isChecked()) //둘다 선택 안 함
            QMessageBox::information(this, "안내","둘 중 하나는 반드시 선택해야 합니다.");
        if(option[0]->isChecked()) //15cm 선택
        {
            selected.SelectSize(true);
            orderWidget->setCurrentIndex(orderWidget->currentIndex()+1);
        }
        else if(option[1]->isChecked()) //30cm 선택
        {
            selected.SelectSize(false);
             orderWidget->setCurrentIndex(orderWidget->currentIndex()+1);
        }
    });

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
    //layout->addWidget(prev);  // 취소 버튼 추가
    layout->addWidget(next);  // 주문 버튼 추가

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

/* 빵 선택 위젯 구성 */
QWidget* SubwayKiosk::selectBread()
{
    /* 사이즈 선택 */
    QWidget *breadWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *sizeLayout = new QVBoxLayout(breadWidget); //수직 레이아웃 생성
    Bread breadType;

    QPushButton *next = new QPushButton; //다음 버튼
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(next);  // 주문 버튼 추가

    QLabel* title = new QLabel("빵 선택");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    QRadioButton *option[6];
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QList<QString> bread = dataManager.sqlManager.GetBreadList();

    for(int i = 0;i<6;i++){
        option[i] = new QRadioButton(bread[i],this);
        option[i]->setStyleSheet("font-size : 20px;");
        btnGroup->addButton(option[i]);
    }

    sizeLayout->addWidget(title);
    sizeLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    for(int i =0;i<6;i++)
    {
        sizeLayout->addWidget(option[i]);
        sizeLayout->setAlignment(option[i], Qt::AlignCenter); //버튼 가운데 정렬
    }
     sizeLayout->addLayout(layout);

    connect(next,&QPushButton::clicked,this,[this, option, &breadType]()
    {
         if (!option[0]->isChecked() && !option[1]->isChecked() && !option[2]->isChecked() && !option[3]->isChecked() && !option[4]->isChecked()&&!option[5]->isChecked()) //아무 것도 선택되지 않음
         {
             QMessageBox::information(this, "안내","빵을 최소 하나 선택해야 합니다.");
             return;
         }
         for(int i = 0;i<6;i++)
       {
             if(option[i]->isChecked())
             {
                  breadType = static_cast<Bread>(i); // enum 값으로 변환
                   selected.SelectBread(breadType);
                 struct select s = selected.GetSelected();
             }
         }
         orderWidget->setCurrentIndex(orderWidget->currentIndex()+1);
     });

    return breadWidget;
}

/* 토핑 선택 위젯 구성 */
QWidget* SubwayKiosk::selectTopping()
{
    QWidget *toppingWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *sizeLayout = new QVBoxLayout(toppingWidget); //수직 레이아웃 생성

    QPushButton *next = new QPushButton; //다음 버튼
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(next);  // 주문 버튼 추가

    QLabel* title = new QLabel("추가 재료");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    QCheckBox *option[7];
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QList<QString> topping = dataManager.sqlManager.GetToppingList();

    for(int i = 0; i < 7; i++) {
        Topping toppingType = static_cast<Topping>(i); // enum 값으로 변환
        option[i] = new QCheckBox(topping[i], this);
        option[i]->setChecked(false); // 기본적으로 체크되지 않도록 설정
        option[i]->setStyleSheet("font-size : 20px;");
        btnGroup->addButton(option[i]);

        // QCheckBox 상태에 따라 selectedToppings 배열 업데이트
        connect(option[i], &QCheckBox::toggled, this, [this, toppingType](bool checked) {
            selectedToppings[static_cast<int>(toppingType)] = checked; // 체크 여부를 bool 배열에 저장
        });
    }

    // 복수 선택 가능하도록 설정;
    btnGroup->setExclusive(false);

    connect(next, &QPushButton::clicked, this, [this]() {
        selected.SelectTopping(selectedToppings);
        orderWidget->setCurrentIndex(orderWidget->currentIndex()+1);

    });

    sizeLayout->addWidget(title);
    sizeLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    for(int i =0;i<7;i++)
    {
        sizeLayout->addWidget(option[i]);
        sizeLayout->setAlignment(option[i], Qt::AlignCenter); //버튼 가운데 정렬
    }
    sizeLayout->addLayout(layout);

    return toppingWidget;
}

/* 치즈 선택 위젯 구성 */
QWidget* SubwayKiosk::selectCheese()
{
    QWidget *cheeseWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *sizeLayout = new QVBoxLayout(cheeseWidget); //수직 레이아웃 생성

    QPushButton *next = new QPushButton; //다음 버튼

    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");


    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(next);  // 주문 버튼 추가

    QLabel* title = new QLabel("치즈");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    QRadioButton *option[3];
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QList<QString> cheese = dataManager.sqlManager.GetCheeseList();

    for(int i = 0;i<3;i++){
        option[i] = new QRadioButton(cheese[i],this);
        option[i]->setStyleSheet("font-size : 20px;");
        btnGroup->addButton(option[i]);
    }

    connect(next,&QPushButton::clicked,this,[this,option](){

        for(int i = 0; i < 3; i++)
        {
            if(option[i]->isChecked())
            {
                Cheese cheeseType = static_cast<Cheese>(i); // enum 값으로 변환
                selected.SelectCheese(cheeseType);
            }
        }
        orderWidget->setCurrentIndex(orderWidget->currentIndex()+1);
  });

    sizeLayout->addWidget(title);
    sizeLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    for(int i =0;i<3;i++)
    {
        sizeLayout->addWidget(option[i]);
        sizeLayout->setAlignment(option[i], Qt::AlignCenter); //버튼 가운데 정렬
    }
    sizeLayout->addLayout(layout);

    return cheeseWidget;
}

/* 야채 선택 위젯 */
QWidget* SubwayKiosk::selectVegetable()
{
    QWidget *vegetableWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *sizeLayout = new QVBoxLayout(vegetableWidget); //수직 레이아웃 생성

    QPushButton *next = new QPushButton; //다음 버튼
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(next);  // 주문 버튼 추가

    QLabel* title = new QLabel("야채");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    QCheckBox *option[8];
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QList<QString> vegetable = dataManager.sqlManager.GetVegetableList();

    for(int i = 0;i<8;i++){
        Vegetable vegetableType = static_cast<Vegetable>(i); // enum 값으로 변환
        option[i] = new QCheckBox(vegetable[i],this);
        option[i]->setStyleSheet("font-size : 20px;");
        btnGroup->addButton(option[i]);

        // 체크박스 선택 시 selectedVegetable 배열 업데이트
        connect(option[i], &QCheckBox::toggled, this, [this, vegetableType](bool checked) {
            selectedVegetables[static_cast<int>(vegetableType)] = checked; // 체크 여부를 bool 배열에 저장
        });
    }
    btnGroup->setExclusive(false); //복수 선택 가능

    sizeLayout->addWidget(title);
    sizeLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    for(int i =0;i<8;i++)
    {
        sizeLayout->addWidget(option[i]);
        sizeLayout->setAlignment(option[i], Qt::AlignCenter); //버튼 가운데 정렬
    }
    sizeLayout->addLayout(layout);

    connect(next,&QPushButton::clicked, this, [this](){
        selected.SelectVegetable(selectedVegetables); //야채 선택 정보 저장
        orderWidget->setCurrentIndex(orderWidget->currentIndex()+1); //다음 페이지로 이동
    });

    return vegetableWidget;
}

/* 소스 선택 위젯 */
QWidget* SubwayKiosk::selectSauce()
{
    QWidget *sauceWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *sauceLayout = new QVBoxLayout(sauceWidget); //수직 레이아웃 생성
    QPushButton *next = new QPushButton; //다음 버튼
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(next);  // 주문 버튼 추가

    QLabel* title = new QLabel("소스");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    QCheckBox *option[14];
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QList<QString> sauce = dataManager.sqlManager.GetSauceList();

    for(int i = 0;i<14;i++){
        Sauce sauceType = static_cast<Sauce>(i); // enum 값으로 변환
        option[i] = new QCheckBox(sauce[i],this);
        option[i]->setStyleSheet("font-size : 20px;");
        btnGroup->addButton(option[i]);

        // 체크박스 선택 시 selectedSauce 배열 업데이트
        connect(option[i], &QCheckBox::toggled, this, [this, sauceType](bool checked){
            selectedSauce[static_cast<int>(sauceType)] = checked; // 체크 여부를 bool 배열에 저장
        });
    }
    btnGroup->setExclusive(false); //복수 선택 가능

    sauceLayout->addWidget(title);
    sauceLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    for(int i =0;i<14;i++)
    {
        sauceLayout->addWidget(option[i]);
        sauceLayout->setAlignment(option[i], Qt::AlignCenter); //버튼 가운데 정렬
    }
    sauceLayout->addLayout(layout);

    connect(next, &QPushButton::clicked, this, [this](){
        selected.SelectSauce(selectedSauce); //소스 선택 정보 저장
        orderWidget->setCurrentIndex(orderWidget->currentIndex()+1); //다음 페이지 이동
    });

    return sauceWidget;
}

/* 세트 선택 위젯 */
QWidget* SubwayKiosk::selectSet()
{
    QWidget *setWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *setLayout = new QVBoxLayout(setWidget); //수직 레이아웃 생성

    QPushButton *next = new QPushButton; //다음 버튼
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(next);  // 주문 버튼 추가

    QLabel* title = new QLabel("세트");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    QCheckBox *option[2];
    QButtonGroup *btnGroup = new QButtonGroup(this);

    option[0] = new QCheckBox("세트",this);
    option[0]->setStyleSheet("font-size : 20px;");
    option[1] = new QCheckBox("단품",this);
    option[1]->setStyleSheet("font-size : 20px;");
    btnGroup->addButton(option[0]);
    btnGroup->addButton(option[1]);

    //다음 버튼 눌렀을 때
    connect(next, &QPushButton::clicked, [this, option]() {
        if (!option[0]->isChecked() && !option[1]->isChecked()) //아무 것도 선택되지 않음
        {
            QMessageBox::information(this, "안내","세트와 단품 중 반드시 하나를 선택해야 합니다.");
            return;
        }

        if (option[0]->isChecked()) { //세트 선택
            selected.SelectSet(true);
            moveNext();
        }
        else if (option[1]->isChecked()) { //단품 선택(마지막 위젯으로)
            selected.SelectSet(false);
            QWidget* finalWidget = selectFinalCheck(); //마지막 선택 확인 위젯 생성
            orderWidget->addWidget(finalWidget);
            orderWidget->setCurrentIndex(orderWidget->count() - 1);
        }
    });

    setLayout->addWidget(title);
    setLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    for(int i =0;i<2;i++)
    {
        setLayout->addWidget(option[i]);
        setLayout->setAlignment(option[i], Qt::AlignCenter); //버튼 가운데 정렬
    }
    setLayout->addLayout(layout);

    return setWidget;
}


/* 세트 종류 선택 위젯 */
QWidget* SubwayKiosk::selectWhichSet()
{
    QWidget *whichSetWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *whichSetLayout = new QVBoxLayout(whichSetWidget); //수직 레이아웃 생성

    QPushButton *next = new QPushButton; //다음 버튼
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(next);  // 주문 버튼 추가

    QLabel* title = new QLabel("세트");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    QCheckBox *option[2];
    QButtonGroup *btnGroup = new QButtonGroup(this);

    option[0] = new QCheckBox("쿠키 세트",this);
    option[0]->setStyleSheet("font-size : 20px;");
    option[1] = new QCheckBox("감자칩 세트",this);
    option[1]->setStyleSheet("font-size : 20px;");
    btnGroup->addButton(option[0]);
    btnGroup->addButton(option[1]);

    //다음 버튼 눌렀을 때
    connect(next, &QPushButton::clicked, [this, option]() {
        if (!option[0]->isChecked() && !option[1]->isChecked()) //아무 것도 선택되지 않음
        {
            QMessageBox::information(this, "안내","쿠키 세트와 감자칩 세트 중 반드시 하나를 선택해야 합니다.");
            return;
        }

        if (option[0]->isChecked()) { //쿠키 세트 선택
            moveNext();
        } else if (option[1]->isChecked()) { //감자칩 세트 선택(다다음 위젯으로)
            orderWidget->setCurrentIndex(orderWidget->currentIndex()+2);
        }
    });

    whichSetLayout->addWidget(title);
    whichSetLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    for(int i =0;i<2;i++)
    {
        whichSetLayout->addWidget(option[i]);
        whichSetLayout->setAlignment(option[i], Qt::AlignCenter); //버튼 가운데 정렬
    }
    whichSetLayout->addLayout(layout);

    return whichSetWidget;
}

/* 쿠키 선택 위젯 */
QWidget* SubwayKiosk::selectCookie()
{
    QWidget *cookieWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *sizeLayout = new QVBoxLayout(cookieWidget); //수직 레이아웃 생성
    Cookie cookieType;

    QPushButton *next = new QPushButton; //다음 버튼
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
   // layout->addWidget(prev);  // 취소 버튼 추가
    layout->addWidget(next);  // 주문 버튼 추가

    QLabel* title = new QLabel("쿠키");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    QRadioButton *option[5];
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QList<QString> cookie = dataManager.sqlManager.GetCookieList();

    for(int i = 0;i<5;i++){
        option[i] = new QRadioButton(cookie[i],this);
        option[i]->setStyleSheet("font-size : 20px;");
        btnGroup->addButton(option[i]);
    }

    sizeLayout->addWidget(title);
    sizeLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    for(int i =0;i<5;i++)
    {
        sizeLayout->addWidget(option[i]);
        sizeLayout->setAlignment(option[i], Qt::AlignCenter); //버튼 가운데 정렬
    }
    sizeLayout->addLayout(layout);

    connect(next,&QPushButton::clicked,this,[this, option, &cookieType]()
    {
        if (!option[0]->isChecked() && !option[1]->isChecked() && !option[2]->isChecked() && !option[3]->isChecked() && !option[4]->isChecked()) //아무 것도 선택되지 않음
        {
            QMessageBox::information(this, "안내","쿠키를 최소 하나 선택해야 합니다.");
            return;
        }

        for(int i = 0;i<5;i++)
        {
            if(option[i]->isChecked())
            {
                cookieType = static_cast<Cookie>(i); // enum 값으로 변환
                selected.SelectCookie(cookieType);
            }
        }
        orderWidget->setCurrentIndex(orderWidget->currentIndex()+2);//감자칩 선택 위젯 건너 뜀
        });

    return cookieWidget;
}
/* 감자칩 선택 위젯 */
QWidget* SubwayKiosk::selectChips()
{
    QWidget *chipsWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *sizeLayout = new QVBoxLayout(chipsWidget); //수직 레이아웃 생성
    Chips chipsType;

    QPushButton *next = new QPushButton; //다음 버튼
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(next);  // 주문 버튼 추가

    QLabel* title = new QLabel("감자칩");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    QRadioButton *option[5];
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QList<QString> chips = dataManager.sqlManager.GetChipsList();

    for(int i = 0;i<5;i++){
        Chips chipsType = static_cast<Chips>(i); // enum 값으로 변환
        option[i] = new QRadioButton(chips[i],this);
        option[i]->setStyleSheet("font-size : 20px;");
        btnGroup->addButton(option[i]);
    }

    sizeLayout->addWidget(title);
    sizeLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    for(int i =0;i<5;i++)
    {
        sizeLayout->addWidget(option[i]);
        sizeLayout->setAlignment(option[i], Qt::AlignCenter); //버튼 가운데 정렬
    }
    sizeLayout->addLayout(layout);

    connect(next,&QPushButton::clicked,this,[this, option, &chipsType]()
        {
                if (!option[0]->isChecked() && !option[1]->isChecked() && !option[2]->isChecked()) //아무 것도 선택되지 않음
                {
                    QMessageBox::information(this, "안내","감자칩을 최소 하나 선택해야 합니다.");
                    return;
                }

                for(int i = 0;i<3;i++)
                {
                    if(option[i]->isChecked())
                    {
                        chipsType = static_cast<Chips>(i); // enum 값으로 변환
                        selected.SelectChips(chipsType);
                    }
                }
                orderWidget->setCurrentIndex(orderWidget->currentIndex()+1);
        });

    return chipsWidget;
}

/* 음료 선택 위젯 */
QWidget* SubwayKiosk::selectDrink()
{
    QWidget *drinkWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *sizeLayout = new QVBoxLayout(drinkWidget); //수직 레이아웃 생성
    Drink drinkType;

    QPushButton *next = new QPushButton; //다음 버튼
    next->setText(QString("다음"));
    next->setStyleSheet("background-color : red; color : white; font : bold;");

    // 버튼 가로 배치할 레이아웃
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(next);  // 주문 버튼 추가

    QLabel* title = new QLabel("음료");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    QRadioButton *option[3];
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QList<QString> drink = dataManager.sqlManager.GetDrinkList();

    for(int i = 0;i<3;i++){
        MainSandwich sandwichType = static_cast<MainSandwich>(i); // enum 값으로 변환
        option[i] = new QRadioButton(drink[i],this);
        option[i]->setStyleSheet("font-size : 20px;");
        btnGroup->addButton(option[i]);
    }

    sizeLayout->addWidget(title);
    sizeLayout->addWidget(line); // 제목과 옵션 사이에 가로줄 추가
    for(int i =0;i<3;i++)
    {
        sizeLayout->addWidget(option[i]);
        sizeLayout->setAlignment(option[i], Qt::AlignCenter); //버튼 가운데 정렬
    }
    sizeLayout->addLayout(layout);

    connect(next,&QPushButton::clicked,this,[this, option, &drinkType]()
            {
                if (!option[0]->isChecked() && !option[1]->isChecked() && !option[2]->isChecked()) //아무 것도 선택되지 않음
                {
                    QMessageBox::information(this, "안내","음료를 최소 하나 선택해야 합니다.");
                    return;
                }

                for(int i = 0;i<3;i++)
                {
                    if(option[i]->isChecked())
                    {
                        drinkType = static_cast<Drink>(i); // enum 값으로 변환
                        selected.SelectDrink(drinkType);
                    }
                }
                QWidget* finalWidget = selectFinalCheck(); //마지막 선택 확인 위젯 생성
                orderWidget->addWidget(finalWidget);
                orderWidget->setCurrentIndex(orderWidget->currentIndex()+1);
            });

    return drinkWidget;
}

/* 마지막 선택 확인 위젯 */
QWidget* SubwayKiosk::selectFinalCheck()
{
    QWidget *finalWidget = new QWidget; //크기 선택 위젯
    QVBoxLayout *layout = new QVBoxLayout(finalWidget); //수직 레이아웃 생성

    QLabel* title = new QLabel("선택 확인");
    title->setStyleSheet("font : bold; font-size : 20px;");

    // 가로줄 추가
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine); // 수평선 설정
    line->setStyleSheet("color: gray;"); // 선 색상 설정

    struct select selectedInfo = selected.GetSelected(); // 선택 정보를 가져옵니다.

    // 선택된 항목 내용을 표시할 QLabel
    QLabel *cartContents = new QLabel;
    cartContents->setStyleSheet("font-size: 16px;");

    // 선택된 내용을 문자열로 포맷팅
    QString contentText = "선택한 샌드위치: " + dataManager.sqlManager.GetDetail(selectedInfo.menu).nameKr + "\n";
    // 빵 선택 여부 확인
    int breadSize = static_cast<int>(selectedInfo.bread);
    if (breadSize >= 0 && breadSize < dataManager.sqlManager.GetBreadList().size()) {
        contentText += "빵: " + dataManager.sqlManager.GetBreadList().at(static_cast<int>(selectedInfo.bread)) + "\n";
    } else {
        contentText += "빵: 선택되지 않음\n"; // 빵이 선택되지 않은 경우 처리
    }

    // 치즈 선택 여부 확인
    int cheeseSize = static_cast<int>(selectedInfo.cheese);
    if (cheeseSize >= 0 && cheeseSize < dataManager.sqlManager.GetCheeseList().size()) {
        contentText += "치즈: " + dataManager.sqlManager.GetCheeseList().at(static_cast<int>(selectedInfo.cheese)) + "\n";
    } else {
        contentText += "치즈: 선택되지 않음\n"; // 치즈가 선택되지 않은 경우 처리
    }

    //topping 선택
    contentText += "추가 재료: ";
    for(int i = 0;i<7;i++){
        if(selectedInfo.topping[i]==true){
            contentText += dataManager.sqlManager.GetToppingList().at(i) + " ";
        }
    }

//    야채 및 소스 선택 추가
    contentText += "\n야채: ";
    for (int i = 0; i < 8; i++) {
        if (selectedInfo.vegetable[i]==true) {
            contentText += dataManager.sqlManager.GetVegetableList().at(i) + " ";
        }
    }

    contentText += "\n소스: ";
    for (int i = 0; i < 14; i++) {
        if (selectedInfo.sauce[i]==true) {
            contentText += dataManager.sqlManager.GetSauceList().at(i) + " ";
        }
    }

    // 마지막 쉼표 제거
    if (contentText.endsWith(", ")) {
        contentText.chop(2);
    }

    cartContents->setText(contentText); // QLabel에 선택 내용 설정

    QPushButton *add = new QPushButton;
    add->setText(QString("장바구니에 추가"));
    add->setStyleSheet("background-color : red; color : white; font : bold;");
    connect(add, &QPushButton::clicked, this, [this, selectedInfo]() {
        addToCartItems(selectedInfo.menu);
        orderModal->close();
    }); //장바구니에 추가

    layout->addWidget(title);
    layout->addWidget(line);
    layout->addWidget(cartContents); // 선택 항목 표시
    layout->addWidget(add); // 장바구니에 추가 버튼

    return finalWidget;
}

void SubwayKiosk::addToCartItems(MainSandwich sandwich) //장바구니 샌드위치 토글에 추가
{
    // 선택된 샌드위치 항목을 표시할 라벨 생성
    QString sandwichName = dataManager.sqlManager.GetDetail(sandwich).nameKr; // 샌드위치 이름 가져오기
    QLabel *sandwichLabel = new QLabel(sandwichName, this);
    sandwichLabel->adjustSize(); // 라벨 크기 조정
     sandwichLayoutToggle->addWidget(sandwichLabel);   // 샌드위치 항목을 토글 아래에 추가

    // 처음에는 항목을 숨김 상태로 설정
    //sandwichLabel->setVisible(toggleSandwich->isChecked());

    // 토글 상태에 따라 항목 보이기/숨기기 연결
    connect(toggleSandwich, &QCheckBox::toggled, this, [sandwichLabel]() {
        sandwichLabel->setVisible(!sandwichLabel->isVisible()); // 토글 상태에 따라 항목 가시성 변경
    });

    // Sandwich 토글과 항목을 QListWidget에 추가
    QListWidgetItem *itemSandwich = new QListWidgetItem(ui->cartList);
     itemSandwich->setSizeHint(sandwichToggleWidget->sizeHint()); // 항목의 크기를 위젯에 맞춤
    ui->cartList->addItem(itemSandwich);
    ui->cartList->setItemWidget(itemSandwich, sandwichToggleWidget);

    cart.Add(selected);
}

void SubwayKiosk::moveNext()
{
    int idx = orderWidget->currentIndex();
    orderWidget->setCurrentIndex(idx+1);
}

void SubwayKiosk::movePrev()
{
    int idx = orderWidget->currentIndex();
    if(idx>0)
        orderWidget->setCurrentIndex(idx-1);
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
