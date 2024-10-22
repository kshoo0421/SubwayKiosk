#ifndef SUBWAYKIOSK_H
#define SUBWAYKIOSK_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QMdiArea>
#include <QFrame>
#include <QDialog>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "ManageFrame.h"
#include "DatabaseManager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SubwayKiosk;
}
QT_END_NAMESPACE

class SubwayKiosk : public QMainWindow
{
    Q_OBJECT

public:
    SubwayKiosk(QWidget *parent = nullptr);
    ~SubwayKiosk();

    DatabaseManager& dataManager = DatabaseManager::Instance(); //db 가져오기

    QDialog *modal = new QDialog(this); //모달 창
    QVBoxLayout *modalLayout = new QVBoxLayout(modal); //모달 담을 레이아웃

    void setMenuTextStyle(); //메뉴 이름 스타일 설정
    void applyBtnStyle( int size, int selectedIdx);
    void applyLabelStyle(QLabel *labels[], int size);

    QStackedWidget *orderWidget = new QStackedWidget;
    QWidget* selectSize(); //사이즈 선택 위젯
    QWidget* selectBread(); //빵 선택 위젯
    QWidget* selectTopping(); //추가 재료 선택 위젯
    QWidget* selectCheese(); // 치즈 선택 위젯
    QWidget* selectVegetable(); //야채 선택 위젯
    QWidget* selectSauce(); //소스 선택 위젯
    QWidget* selectCookie(); //쿠키 선택 위젯
    QWidget* selectDrink(); //음료 선택 위젯
    QWidget* selectChips(); //감자칩 선택 위젯

public slots:
    void SihooTest();
    void closeModal(); //모달 종료
    void selectOrder(); //주문 선택
    void moveNext(); //다음 페이지 이동
    void movePrev(); //이전 페이지 이동

private:
    Ui::SubwayKiosk *ui;
};
#endif // SUBWAYKIOSK_H
