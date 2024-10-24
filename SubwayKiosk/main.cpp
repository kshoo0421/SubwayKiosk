#include "subwaykiosk.h"
#include <QApplication>
//6조
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SubwayKiosk w;

    w.show();

    return a.exec();
}
