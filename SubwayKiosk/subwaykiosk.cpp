#include "subwaykiosk.h"
#include "./ui_subwaykiosk.h"

SubwayKiosk::SubwayKiosk(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SubwayKiosk)
{
    ui->setupUi(this);
}

SubwayKiosk::~SubwayKiosk()
{
    delete ui;
}
