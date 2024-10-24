#include "ManageFrame.h"
#include <QMouseEvent>

ManageFrame::ManageFrame(QWidget * parent):  QFrame(parent) { }

const QMap<int,QString> ManageFrame::imagePaths = {
    {0, ":/Resources/eggMayo.png"},
    {1,":/Resources/ham.png"},
    {2,  ":/Resources/tuna.png"},
    {3, ":/Resources/blt.png"},
    {4, ":/Resources/italianBMT.png"},
    {5, ":/Resources/veggie.png"},
    {6, ":/Resources/chickenSlice.png"},
    {7, ":/Resources/subwayClub.png"},
    {8, ":/Resources/rotisserieBBQ.png"},
    {9, ":/Resources/roastedChicken.png"},
    {10,":/Resources/chickenTeriyaki.png"},
    {11,":/Resources/spicyItalian.png"},
    {12,":/Resources/pulledPorkBBQ.png"},
    {13,":/Resources/steak_Cheese.png"},
    {14,":/Resources/chickenBaconAvocado.png"},
    {15,":/Resources/shrimp.png"},
    {16, ":/Resources/kBBQ.png"},
    {17,":/Resources/spicyShrimp.png"},
    {18,":/Resources/kBBQ.png"},
    {19,":/Resources/shrimp.png"},
    {20,":/Resources/beef_mushroom.png"},
    {21,":/Resources/beef.png"},
};

QPixmap ManageFrame::getImage(int n) const {
    QString path = imagePaths.value(n,QString());
    return QPixmap(imagePaths.value(n, QString())); // 프레임 번호에 해당하는 이미지 반환, 기본값은 빈 문자열
}

void ManageFrame::mousePressEvent(QMouseEvent *event)
{
    emit frameClicked(); // 프레임 클릭 시 신호 발생
    QFrame::mousePressEvent(event);
}

