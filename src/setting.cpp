#include "setting.h"
#include <QDebug>
#include <QSettings>

Setting::Setting(QWidget *parent)
  : QWidget(parent)
{
//    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    dirlab = new QLabel;
    mirrorlab = new QLabel;
    delaylab = new QLabel;
    scalelab = new QLabel;
    cameraDevicelab = new QLabel;
    vedioDevicelab = new QLabel;

    cameraDevice = new QPushButton(this);
    vedioDevice = new QPushButton(this);
    dir = new QPushButton(this);
    scale = new QPushButton(this);

    delaybtn = new SwitchButton(this);
    mirrorbtn = new SwitchButton(this);

    vlayout = new QVBoxLayout;
    delayLayout = new QHBoxLayout;
    mirrorLayout = new QHBoxLayout;
    dirLayout = new QHBoxLayout;
    scaleLayout = new QHBoxLayout;
    cameraDeviceLayout = new QHBoxLayout;
    vedioDeviceLayout = new QHBoxLayout;

//    current_dir = new QString;
    current_dir_lab = new QLabel;
    delaybtn->setFixedWidth(40);
    mirrorbtn->setFixedWidth(40);
//    current_dir_lab->setText(":/home");
    current_dir_lab->setStyleSheet(
          "font-size: 12px;"
          "font-family: Noto Sans CJK SC;"
          "font-weight: 400;"
          "line-height: 14px;"
          "color: rgba(255, 255, 255, 0.5);"
          "opacity: 1;"
          );
//    current_dir_lab->setSizePolicy();
    delaylab->setText(tr("Delayed shooting"));
    mirrorlab->setText(tr("Image mirroring"));
    dirlab->setText(tr("The image path"));
    scalelab->setText(tr("The image scale"));
    cameraDevicelab->setText(tr("Camera device"));
    vedioDevicelab->setText(tr("Sound device"));
    QString btnStyle = \
        "width: 204px;"
        "height: 30px;"
        "background: #27282A;"
        "opacity: 1;"
        "border-radius: 4px;"
    ;

    QString labStyle = \
        "font-size: 14px;"
        "font-family: Noto Sans CJK SC;"
        "font-weight: 400;"
        "line-height: 32px;"
        "color: #FFFFFF;"
        "opacity: 1;";
    dirlab->setStyleSheet(labStyle);
    mirrorlab->setStyleSheet(labStyle);
    delaylab->setStyleSheet(labStyle);
    scalelab->setStyleSheet(labStyle);
    cameraDevicelab->setStyleSheet(labStyle);
    vedioDevicelab->setStyleSheet(labStyle);

    dir->setStyleSheet(btnStyle);
    cameraDevice->setStyleSheet(btnStyle);
    vedioDevice->setStyleSheet(btnStyle);
    scale->setStyleSheet(btnStyle);
    //设置按钮布局
    scaleLayout->addSpacing(8);
    scaleLayout->addWidget(scalelab);
    scaleLayout->setMargin(0);
    scale->setLayout(scaleLayout);

    vedioDeviceLayout->addSpacing(8);
    vedioDeviceLayout->addWidget(vedioDevicelab);
    vedioDeviceLayout->setMargin(0);
    vedioDevice->setLayout(vedioDeviceLayout);

    dirLayout->addSpacing(8);
    dirLayout->addWidget(dirlab);
    dirLayout->setMargin(0);
    dirLayout->addWidget(current_dir_lab);
    dir->setLayout(dirLayout);

    cameraDeviceLayout->addSpacing(8);
    cameraDeviceLayout->addWidget(cameraDevicelab);
    cameraDeviceLayout->setMargin(0);
    cameraDevice->setLayout(cameraDeviceLayout);

//    vedioDeviceLayout->addSpacing(8);
    vedioDeviceLayout->addWidget(vedioDevicelab);
    vedioDeviceLayout->setMargin(0);
    vedioDevice->setLayout(vedioDeviceLayout);

    delayLayout->addSpacing(8);
    delayLayout->addWidget(delaylab);
    delayLayout->addSpacing(0);
    delayLayout->addWidget(delaybtn);

    mirrorLayout->addSpacing(8);
    mirrorLayout->addWidget(mirrorlab);
    mirrorLayout->addSpacing(0);
    mirrorLayout->addWidget(mirrorbtn);


    vlayout->addLayout(delayLayout);
    vlayout->addLayout(mirrorLayout);
    vlayout->addWidget(dir);
    vlayout->addWidget(scale);
    vlayout->addWidget(cameraDevice);
    vlayout->addWidget(vedioDevice);
    this->setLayout(vlayout);
//  lineedit->setClearButtonEnabled(setClearButtonEnabled(true);

    connect(dir,&QPushButton::clicked,this,&Setting::dir_click);

}
//void Setting::dir_change(){}
void Setting::dir_click(){
  current_dir = QFileDialog::getExistingDirectory(nullptr,tr("Select the directory"),":/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if(QDir(current_dir).exists() && current_dir != ""){
    current_dir_lab->setText(current_dir);
  }
  qDebug() << "current_dir"<< current_dir;
  emit dir_change();
}
