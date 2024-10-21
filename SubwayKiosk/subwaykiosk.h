#ifndef SUBWAYKIOSK_H
#define SUBWAYKIOSK_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QMdiArea>
#include <QFrame>

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

    void SihooTest();

    void setMenuTextStyle(); //메뉴 이름 스타일 설정
    void applyBtnStyle( int size, int selectedIdx);
    void applyLabelStyle(QLabel *labels[], int size);

private:
    Ui::SubwayKiosk *ui;
};
#endif // SUBWAYKIOSK_H
