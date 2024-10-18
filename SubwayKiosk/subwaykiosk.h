#ifndef SUBWAYKIOSK_H
#define SUBWAYKIOSK_H

#include <QMainWindow>

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

    void setMenuTextStyle(); //메뉴 이름 스타일 설정

private:
    Ui::SubwayKiosk *ui;
};
#endif // SUBWAYKIOSK_H
