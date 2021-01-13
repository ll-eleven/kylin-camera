#include "button.h"
#include <QDebug>
bool Button::vedio_start = false;
bool Button::vedio_mode = false;
bool Button::voice_mode = false;
Button::Button(QWidget *parent)
  : QWidget(parent)
{
    btnLayout = new QHBoxLayout;

    capture = new QPushButton ;
    vedio = new QPushButton;
    Burst = new QPushButton;  //连拍
    cheese = new QPushButton(this);
    voice = new QPushButton(this);
    picture = new QPushButton;
    stop = new QPushButton(this);
    cheese_vedio = new QPushButton(this);
    cheese_stop = new QPushButton(this);
    restore = new QPushButton;
    this->setMinimumHeight(50);
    this->setFixedHeight(50);

    btnLayout->addSpacing(10);
    btnLayout->addWidget(capture);
    btnLayout->addSpacing(5);
    btnLayout->addWidget(vedio);
    btnLayout->addStretch(90);
//    btnLayout->addWidget(voice);
    btnLayout->addSpacing(5);
    btnLayout->addWidget(cheese);
    btnLayout->addWidget(cheese_vedio);
    btnLayout->addWidget(cheese_stop);
    btnLayout->addSpacing(5);
//    btnLayout->addWidget(stop);
    btnLayout->addWidget(restore);
    btnLayout->addStretch(99);
//    btnLayout->addWidget(Burst);
    btnLayout->addSpacing(5);
    btnLayout->addWidget(picture);
    btnLayout->addSpacing(10);

    btnLayout->setMargin(0);
    btnLayout->setSpacing(0);
    this->setLayout(btnLayout);
//    this->setStyleSheet("QWidget{border-radius:6px;background-color:#000000;}");

    btnLayout->setSpacing(0);

    cheese_vedio->hide();
    cheese_stop->hide();
    restore->hide();
    stop->hide();
    voice->hide();

    QString str = \
      "width: 42px;"
      "height: 32px;"
      "background: #3D6BE5;"
      "opacity: 1;"
      "border-radius: 4px;";

    cheese_stop->setFixedSize(50,50);
    cheese_vedio->setFixedSize(50,50);
    cheese->setFixedSize(50,50);
    capture->setFixedSize(42,32);
    vedio->setFixedSize(42,32);
    picture->setFixedSize(42,32);
//    Burst->setFixedSize(42,32);

    if(set->value("model").toInt()){
        cheese->show();
        cheese_vedio->hide();
        cheese_stop->hide();

        voice->hide();
        stop->hide();
        vedio_mode = false;
        capture->setStyleSheet("QPushButton{background-color:#3D6BE5;border-radius:4px;}");
    //    vedio->setStyleSheet("QPushButton{background-color:#000000}");
    }
  else{
      vedio_mode = true;
      vedio->setStyleSheet("QPushButton{background-color:#3D6BE5;border-radius:4px;}");
//      capture->setStyleSheet("QPushButton{background-color:#000000}");
      cheese->hide();
      cheese_vedio->show();
//      stop->show();
//      voice->show();
    }

    QString btnStyle = "QPushButton{background-color:#3D6BE5}"
                     "QPushButton{border-radius:4px;}"
                     "QPushButton:hover{background-color:rgb(180,180,180);}"
                     "QPushButton:pressed{background-color:rgb(180,180,180);}";

//  capture->setStyleSheet(btnStyle);
    capture->setIcon(QIcon(":/image/camera1.png"));
    vedio->setIcon(QIcon(":/image/vedio1.png"));
    cheese->setIcon(QIcon(":/image/paizhao-kaishi.png"));
    voice->setIcon(QIcon(":/image/maike-on .svg"));
//    Burst->setIcon(QIcon(":/image/burst1.png"));
    picture->setIcon(QIcon(":/image/picture1.png"));
    cheese_vedio->setIcon(QIcon(":/image/luxiang-kaishi.png"));
    cheese_stop->setIcon(QIcon(":/image/luxiang-zanting.png"));
    stop->setIcon(QIcon(":/image/zanting1.png"));
    restore->setIcon(QIcon(":/image/media-playback-start-symbolic.png"));

    capture->setProperty("isWindowButton", 0x1);
    capture->setProperty("useIconHighlightEffect", 0x2);
    capture->setFlat(true);

    vedio->setProperty("isWindowButton", 0x1);
    vedio->setProperty("useIconHighlightEffect", 0x2);
    vedio->setFlat(true);


//  capture->setStyleSheet(btnStyle);
//  cheese->setStyleSheet(btnStyle);
//  stop->setStyleSheet(btnStyle);
//  voice->setIconSize(QSize(30,30));
//    picture->setStyleSheet("QPushButton:hover{background-color:#3D6BE5;}");
//    Burst->setStyleSheet("QPushButton:hover{background-color:#3D6BE5;}");
//    cheese_vedio->setStyleSheet("QPushButton:hover{background-color:#3D6BE5;}");
    cheese->setIconSize(QSize(50,50));
    capture->setIconSize(QSize(22,20));
    vedio->setIconSize(QSize(22,20));
    voice->setIconSize(QSize(22,20));
    stop->setIconSize(QSize(22,20));
    restore->setIconSize(QSize(22,20));
//    Burst->setIconSize(QSize(22,20));
    picture->setIconSize(QSize(22,20));
    cheese_vedio->setIconSize(QSize(35,35));
    cheese_stop->setIconSize(QSize(35,35));
    capture->setFlat(true);
    vedio->setFlat(true);
    voice->setFlat(true);
    cheese->setFlat(true);
    stop->setFlat(true);
    cheese_vedio->setFlat(true);
    cheese_stop->setFlat(true);
    picture->setFlat(true);

    capture->setFocusPolicy(Qt::NoFocus);
    vedio->setFocusPolicy(Qt::NoFocus);
    voice->setFocusPolicy(Qt::NoFocus);
    cheese->setFocusPolicy(Qt::NoFocus);
    stop->setFocusPolicy(Qt::NoFocus);
    cheese_vedio->setFocusPolicy(Qt::NoFocus);
    cheese_stop->setFocusPolicy(Qt::NoFocus);
    picture->setFocusPolicy(Qt::NoFocus);


    picture->setAutoFillBackground(0);

//    this->setAttribute(Qt::WA_Hover, true);
//  this->show();

    connect(capture,&QPushButton::clicked,this,&Button::capture_click);
    connect(vedio,&QPushButton::clicked,this,&Button::vedio_click);
    connect(cheese,&QPushButton::clicked,this,&Button::cheese_click);
    connect(cheese_vedio,&QPushButton::clicked,this,&Button::cheese_vedio_click);
    connect(cheese_stop,&QPushButton::clicked,this,&Button::cheese_stop_click);
    connect(voice,&QPushButton::clicked,this,&Button::voice_click);
    connect(stop,&QPushButton::clicked,this,&Button::stop_click);
    connect(picture,&QPushButton::clicked,this,&Button::picture_click);
    connect(restore,&QPushButton::clicked,this,&Button::restore_click);
//    connect(Burst,&QPushButton::clicked,this,&Button::Burst_click);
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

void Button::focusInEvent(){
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
}


void Button::capture_click(){
    //开始录像时不能切换
    if(!vedio_start){
        cheese->show();
        cheese_vedio->hide();
        cheese_stop->hide();
//        voice->hide();
//        stop->hide();
        vedio_mode = false;
        capture->setStyleSheet("QPushButton{background-color:#3D6BE5;border-radius:4px;}");
        vedio->setStyleSheet("QPushButton{background-color:#000000}");
        set->setValue("model",1);
    }
}

void Button::vedio_click(){
    if(!vedio_start){
        vedio_mode = true;
//        voice->show();
//        stop->show();
        vedio->setStyleSheet("QPushButton{background-color:#3D6BE5;border-radius:4px;}");
        capture->setStyleSheet("QPushButton{background-color:#000000}");
        cheese->hide();
        cheese_vedio->show();
        set->setValue("model",0);
    }
}

void Button::Burst_click(){
//    if(!Burst_mode){
//        Burst_mode = true;
//        Burst->setStyleSheet("QPushButton{background-color:#3D6BE5;border-radius:4px;}");
//        capture->setStyleSheet("QPushButton{background-color:#000000}");
//        vedio->setStyleSheet("QPushButton{background-color:#000000}");

//    }
//    else{
//        Burst->setStyleSheet("QPushButton{background-color:#000000}");
//        Burst_mode = false;
//    }
}
void Button::cheese_click(){
    //拍照模式
    if(!vedio_mode){
         cheese->setIcon(QIcon(":/image/paizhao-kaishi.png"));
      }
}


void Button::cheese_vedio_click(){
    //录像开始
    if(CameraPage::has_device){
     vedio_start = 1;
     cheese_stop->show();
     cheese_vedio->hide();
    }

}

void Button::cheese_stop_click(){
    vedio_start = 0;
    cheese_stop->hide();
    cheese_vedio->show();
    if(!restore->isHidden()){
//        restore->hide();
//        stop->show();
    }
}

void Button::voice_click(){
    //关闭录音设备
    if(!vedio_start){
        if(voice_mode){
              voice->setIcon(QIcon(":/image/maike-off .svg"));
              voice_mode = false;
          }
        //打开录音设备
        else{
            voice->setIcon(QIcon(":/image/maike-on .svg"));
            voice_mode = true;
        }
    }
}
void Button::stop_click(){
    if(CameraPage::has_device && (vedio_start)){
//        restore->show();
//        stop->hide();
    }
}
void Button::restore_click(){
//    stop->show();
//    restore->hide();
}

void Button::picture_click(){
    if(!picturepage_show){
        picture->setStyleSheet("QPushButton{background-color:#3D6BE5;border-radius:4px;}");
        picturepage_show = true;
    }
    else{
        picture->setStyleSheet("QPushButton{background-color:#000000}");
        picturepage_show = false;
    }
}

void Button::scale_click(){

}

