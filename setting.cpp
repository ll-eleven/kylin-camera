#include "setting.h"

Setting::Setting(QWidget *parent)
  : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    dirlab = new QLabel;
    mirrorlab = new QLabel;
    delaylab = new QLabel;
    scalelab = new QLabel;

    cameraDevice = new QPushButton;
    vedioDevice = new QPushButton;
    dir = new QPushButton;
    scale = new QPushButton;

    vedioDevice = new QPushButton;
    delaybtn = new SwitchButton;
    mirrorbtn = new SwitchButton;

    vlayout = new QVBoxLayout;
//    vlayout->addLayout(delayLayout);
//    vlayout->addLayout(mirrorLayout);
    vlayout->addWidget(dir);
    vlayout->addWidget(scale);
    vlayout->addWidget(cameraDevice);
    vlayout->addWidget(vedioDevice);
    this->setLayout(vlayout);
//  lineedit->setClearButtonEnabled(setClearButtonEnabled(true);
}
