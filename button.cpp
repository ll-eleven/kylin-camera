#include "button.h"
#include <QDebug>

Button::Button(QWidget *parent)
  : QWidget(parent)
{
  btnLayout = new QHBoxLayout;

  capture = new QPushButton(this);
  vedio = new QPushButton(this);
  Burst = new QPushButton(this);  //连拍
  cheese = new QPushButton(this);
  voice = new QPushButton(this);
  picture = new QPushButton(this);
  stop = new QPushButton(this);
  cheese_vedio = new QPushButton(this);
  cheese_stop = new QPushButton(this);

  this->setFixedHeight(50);
  btnLayout->addSpacing(10);
  btnLayout->addWidget(capture);
//  btnLayout->addSpacing(5);
  btnLayout->addWidget(vedio);
  btnLayout->addStretch(99);
  btnLayout->addWidget(voice);
  btnLayout->addSpacing(5);
  btnLayout->addWidget(cheese);
  btnLayout->addWidget(cheese_vedio);
  btnLayout->addWidget(cheese_stop);
  btnLayout->addSpacing(5);
  btnLayout->addWidget(stop);
  btnLayout->addStretch(99);
  btnLayout->addWidget(Burst);
  btnLayout->addSpacing(5);
  btnLayout->addWidget(picture);
  btnLayout->setMargin(0);
  btnLayout->setSpacing(0);
  this->setLayout(btnLayout);
  this->setStyleSheet("border-top-left-radius:6px;QWidget{background-color:#000000}");

  btnLayout->setSpacing(0);

  cheese_vedio->hide();
  cheese_stop->hide();
  cheese_stop->setFixedSize(50,50);
  cheese_vedio->setFixedSize(50,50);
  cheese->setFixedSize(50,50);
  capture->setFixedSize(30,30);
  vedio->setFixedSize(30,30);
//  this->setAttribute(Qt::WA_TranslucentBackground, false);
//  voice->hide();
//  this->setStyleSheet("background-color:#FFFFFF");
//  capture->setFlat(true);
//  this->setAttribute(Qt::WA_TranslucentBackground, true);


  QString btnStyle = "QPushButton{background-color:#3D6BE5}"
                     "QPushButton{border-radius:4px;}"
                     "QPushButton:hover{background-color:rgb(180,180,180);}"
                     "QPushButton:pressed{background-color:rgb(180,180,180);}";
  capture->setStyleSheet(btnStyle);
  cheese->setIcon(QIcon(":/image/paizhao-kaishi.png"));
  capture->setIcon(QIcon(":/image/camera1.png"));
  vedio->setIcon(QIcon(":/image/vedio1.png"));
//  cheese->setIcon(QIcon(":/image/paizhao-kaishi.png"));
//  voice->setIcon(QIcon(":/image/maike-on .svg"));
  Burst->setIcon(QIcon(":/image/burst1.png"));
  picture->setIcon(QIcon(":/image/picture1.png"));
  cheese_vedio->setIcon(QIcon(":/image/luxiang-kaishi.png"));
  cheese_stop->setIcon(QIcon(":/image/luxiang-zanting.png"));

//  capture->setStyleSheet(btnStyle);
//  cheese->setStyleSheet(btnStyle);
//  stop->setStyleSheet(btnStyle);
//  voice->setIconSize(QSize(30,30));
  cheese->setIconSize(QSize(40,40));
  cheese_vedio->setIconSize(QSize(35,35));
  cheese_stop->setIconSize(QSize(35,35));
  capture->setFlat(true);
  vedio->setFlat(true);
  voice->setFlat(true);
  cheese->setFlat(true);
  stop->setFlat(true);
  Burst->setFlat(true);
  picture->setFlat(true);
//  this->show();

  connect(capture,&QPushButton::clicked,this,&Button::capture_click);
  connect(vedio,&QPushButton::clicked,this,&Button::vedio_click);
  connect(cheese,&QPushButton::clicked,this,&Button::cheese_click);
  connect(cheese_vedio,&QPushButton::clicked,this,&Button::cheese_vedio_click);
  connect(cheese_stop,&QPushButton::clicked,this,&Button::cheese_stop_click);
  connect(voice,&QPushButton::clicked,this,&Button::voice_click);
//  connect(stop,&QPushButton::clicked,this,&Button::stop_click);
  connect(picture,&QPushButton::clicked,this,&Button::picture_click);
  connect(stop,&QPushButton::clicked,this,&Button::stop_click);
  //拍照按钮的图标变换
  connect(cheese,&QPushButton::pressed,this,[=](){
      if(!vedio_mode)
      {
          cheese->setIcon(QIcon(":/image/paizhao-dianji.png"));
       }

    });

//  this->setStyleSheet("background-color:#000000;");
}

Button::~Button(){

}
void Button::capture_click(){

  cheese->show();
  cheese_vedio->hide();
  cheese_stop->hide();
  voice->setIcon(QIcon(""));
  stop->setIcon(QIcon(""));
  vedio_mode = false;
  capture->setStyleSheet("QPushButton{background-color:#3D6BE5;border-radius:4px;}");
  vedio->setStyleSheet("QPushButton{background-color:#000000}");

}

void Button::vedio_click(){
    vedio_mode = true;
    voice->setIcon(QIcon(":/image/maike-on .svg"));
    stop->setIcon(QIcon(":/image/zanting1.png"));
    vedio->setStyleSheet("QPushButton{background-color:#3D6BE5;border-radius:4px;}");
    capture->setStyleSheet("QPushButton{background-color:#000000}");

    cheese->hide();
    cheese_vedio->show();

}
void Button::cheese_click(){
    //拍照模式
    if(!vedio_mode){
         cheese->setIcon(QIcon(":/image/paizhao-kaishi.png"));
      }

}
void Button::cheese_vedio_click(){
    //录像开始

     vedio_start = 1;
     cheese_stop->show();
     cheese_vedio->hide();


}

void Button::cheese_stop_click(){
    vedio_start = 0;
    cheese_stop->hide();
    cheese_vedio->show();
}

void Button::voice_click(){

    if(vedio_mode){
          voice->setIcon(QIcon(":/image/maike-off .svg"));
      }
    else{

      }
}
void Button::stop_click(){

}
void Button::picture_click(){

}
void Button::Burst_click(){

}
void Button::scale_click(){

}

