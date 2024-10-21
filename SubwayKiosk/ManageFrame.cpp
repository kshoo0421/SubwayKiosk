#include "ManageFrame.h"
#include <QMouseEvent>

ManageFrame::ManageFrame(QWidget * parent):  QFrame(parent) { }

const QMap<int,QString> ManageFrame::imagePaths = {
    {0, ":/Resources/eggMayo.png"},
    {1,":/Resources/ham.png"},
    {2,  ":/Resources/tuna.png"},
    {3, ":/Resources/blt.png"},
    {4, ":/Resources/italianBMT.png"},
};

QPixmap ManageFrame::getImage(int n) const {
    QString path = imagePaths.value(n,QString());
    qDebug()<<"path = "<<path;
    return QPixmap(imagePaths.value(n, QString())); // 프레임 번호에 해당하는 이미지 반환, 기본값은 빈 문자열
}

void ManageFrame::mousePressEvent(QMouseEvent *event)
{
    emit frameClicked(); // 프레임 클릭 시 신호 발생
    QFrame::mousePressEvent(event);
}

