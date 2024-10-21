#ifndef SUBWAYKIOSK_H
#define SUBWAYKIOSK_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QMdiArea>
#include <QFrame>
#include <QDialog>
#include <QVBoxLayout>
#include "ManageFrame.h"

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




    QDialog *modal = new QDialog(this); //모달 창
    QVBoxLayout *modalLayout = new QVBoxLayout(modal); //모달 담을 레이아웃

    void setMenuTextStyle(); //메뉴 이름 스타일 설정
    void applyBtnStyle( int size, int selectedIdx);
    void applyLabelStyle(QLabel *labels[], int size);

    QWidget* selectSize(); //사이즈 선택 위젯 생성

public slots:
    void SihooTest();
    void closeModal(); //모달 종료
    void selectOrder(); //주문 선택


private:
    Ui::SubwayKiosk *ui;
};
#endif // SUBWAYKIOSK_H
