#include "setting.h"
#include <QDebug>
#include <QSettings>
#include <QStandardPaths>
#include <QMessageBox>
#include <QErrorMessage>
#include "unistd.h"


Setting::Setting(QWidget *parent)
  : QWidget(parent)
{
//    this->setWindowFlags(Qt::FramelessWindowHint);
    init_ui();
//    this->setStyleSheet("QWidget{border-radius:6px;background-color:#123000;}");
}

void Setting::init_ui(){
    this->setAttribute(Qt::WA_StyledBackground);

    mirrorlab = new QLabel;
    delaylab = new QLabel;
    setlab = new QLabel;
    themelab = new QLabel;
    helplab = new QLabel;
    aboutlab = new QLabel;

    delay = new QWidget;
    mirror = new QWidget;
    set = new QPushButton;
    theme = new QPushButton;
    help = new QPushButton;
    about = new QPushButton;
    mirrorbtn = new SwitchButton;
    delaybtn = new SwitchButton;

    vlayout = new QVBoxLayout;
    delayLayout = new QHBoxLayout;
    mirrorLayout = new QHBoxLayout;
    settingLayout = new QHBoxLayout;
    themeLayout = new QHBoxLayout;
    helpLayout = new QHBoxLayout;
    aboutLayout = new QHBoxLayout;

    delaybtn->setFixedWidth(40);
    mirrorbtn->setFixedWidth(40);
    delay->setFixedHeight(40);
    mirror->setFixedHeight(40);
    set->setFixedHeight(40);
    about->setFixedHeight(40);
    theme->setFixedHeight(40);
    help->setFixedHeight(40);

    delaylab->setText(tr("Delayed shooting"));
    mirrorlab->setText(tr("Image mirroring"));
    setlab->setText(tr("setting"));
    themelab->setText(tr("theme"));
    helplab->setText(tr("help"));
    aboutlab->setText(tr("about"));
    QString btnStyle = \
        "opacity: 1;"
        "border-radius: 4px;";
            "background-color:#000000";

    QString labStyle = \
            "width: 56px;"
            "height: 20px;"
            "font-size: 14px;"
            "font-family: PingFangSC-Regular;"
            "line-height: 24px;"
//            "color: #FFFFFF;"
            "opacity: 0.91;";


    mirrorlab->setStyleSheet(labStyle);
    delaylab->setStyleSheet(labStyle);
    setlab->setStyleSheet(labStyle);
    themelab->setStyleSheet(labStyle);
    helplab->setStyleSheet(labStyle);
    aboutlab->setStyleSheet(labStyle);

    set->setStyleSheet(btnStyle);
    theme->setStyleSheet(btnStyle);
    help->setStyleSheet(btnStyle);



    //设置按钮布局
    delayLayout->addSpacing(8);
    delayLayout->addWidget(delaylab);
    delayLayout->addStretch(10);
    delayLayout->addWidget(delaybtn);

    mirrorLayout->addSpacing(8);
    mirrorLayout->addWidget(mirrorlab);
    mirrorLayout->addStretch(99);
    mirrorLayout->addWidget(mirrorbtn);

    settingLayout->addSpacing(16);
    settingLayout->addWidget(setlab);
    settingLayout->addStretch(99);
    settingLayout->setMargin(0);

    themeLayout->addSpacing(16);
    themeLayout->addWidget(themelab);
    themeLayout->addStretch(99);
    themeLayout->setMargin(0);

    helpLayout->addSpacing(16);
    helpLayout->addWidget(helplab);
    helpLayout->addStretch(99);
    helpLayout->setContentsMargins(0,0,0,0);

    aboutLayout->addSpacing(16);
    aboutLayout->addWidget(aboutlab);
    aboutLayout->addStretch(99);
    aboutLayout->setMargin(0);
//    setLayout->addSpacing(8);
//    setLayout->set();

    delay->setLayout(delayLayout);
    mirror->setLayout(mirrorLayout);
    set->setLayout(settingLayout);
    theme->setLayout(themeLayout);
    help->setLayout(helpLayout);
    about->setLayout(aboutLayout);

    vlayout->addWidget(delay);
//    vlayout->addWidget(mirror);
    vlayout->addWidget(set);
    vlayout->addWidget(theme);
    vlayout->addWidget(help);
    vlayout->addWidget(about);
    vlayout->setMargin(0);
    this->setLayout(vlayout);

}

