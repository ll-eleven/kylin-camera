#include "aboutwidget.h"
#include <QDebug>
#include <QScreen>
#include <QRect>
#include <QGuiApplication>
#define VERSION "1.1.2kord8"

AboutWidget::AboutWidget(const StyleWidgetAttribute& swa, QString dialogTitleText, bool isDialog )
    :local_swa(swa)
{
    m_isDialog=isDialog;
    this->setWindowIcon(QIcon("/usr/share/icons/ukui-icon-theme-default/64x64@2x/appskylin-camera.png"));
    this->setWindowTitle(tr("Kylin-camera"));
    this->setWindowModality(Qt::ApplicationModal);
    myStyle(swa);
}


AboutWidget::~AboutWidget()
{

}


void AboutWidget::WidgetStyleClose()
{
    //emit doSomethig();
    emit allClose();
    this->close();
}


void AboutWidget::myStyle(StyleWidgetAttribute swa)
{
    //窗口设置
//    this->setWindowFlags(Qt::FramelessWindowHint);// | Qt::Popup);//无边框
//    this->setAttribute(Qt::WA_TranslucentBackground, true);//窗体透明
    this->setFixedSize(swa.w,swa.h);


//    QRect availableGeometry = qApp->primaryScreen()->availableGeometry();
//    this->move((availableGeometry.width() - this->width())/2 + 2 * this->width(), (availableGeometry.height() - this->height())/2);

    //设置阴影

    //this->show();

    //控件
    title = new QWidget;//标题栏
    title->setMaximumHeight(swa.titleHeight);
    title->setMinimumHeight(swa.titleHeight);
    title->setObjectName("title");


    body = new QWidget;//窗体
    body->setFixedHeight(this->height()-title->height()-swa.shadow*2);
    body->setObjectName("body");

    QSize smallWidgetSize(30,30);//小按钮大小

//    widgetClose =new QPushButton;//关闭按钮
//    widgetClose->setObjectName("widgetClose");
//    widgetClose->setIconSize(smallWidgetSize);
//    widgetClose->setFixedSize(smallWidgetSize);
//    connect(widgetClose,&QPushButton::clicked,this,&AboutWidget::WidgetStyleClose);

//    //布局
    QHBoxLayout *hlt0=new QHBoxLayout;//右上角按钮内部，水平布局
    hlt0->setMargin(0);
    hlt0->setSpacing(0);
//    hlt0->addWidget(widgetClose, 1);

    QHBoxLayout *hlt=new QHBoxLayout;//标题栏内部，水平布局
    hlt->setMargin(0);
    hlt->setSpacing(0);
    hlt->addStretch(99);
    hlt->addLayout(hlt0,1);
    hlt->addSpacing(8);

    QVBoxLayout *vlt_temp=new QVBoxLayout;//标题栏内部，水平布局
    vlt_temp->setMargin(0);
    vlt_temp->setSpacing(0);
    vlt_temp->addSpacing(6);
    vlt_temp->addLayout(hlt,1);
    vlt_temp->addStretch(99);

    title->setLayout(vlt_temp);

    QHBoxLayout *hlt2=new QHBoxLayout;//标题栏外部
    hlt2->setMargin(0);
    hlt2->setSpacing(0);
    hlt2->addSpacing(swa.shadow);
    hlt2->addWidget(title);
    hlt2->addSpacing(swa.shadow);

    aboutIcon = new QLabel;

    aboutIcon->setPixmap(QPixmap::fromImage(QImage("/usr/share/icons/ukui-icon-theme-default/64x64@2x/apps/kylin-camera.png")));
    aboutIcon->setScaledContents(true);
//    aboutIcon->setIconedSize(96,96);

    aboutText = new QLabel;

    aboutText->setText(tr("kylin-camera"));
    aboutText->setStyleSheet("font-size:25px;");

    aboutVersion_1 = new QLabel;
    aboutVersion_1->setText(tr("Version:"));
    aboutVersion_2 = new QLabel;
    aboutVersion_2->setText(VERSION);

    aboutMail_1 = new QLabel;
    aboutMail_1->setText(tr("support"));
    aboutMail_2 = new QLabel;
    aboutMail_2->setText("support@kylinos.cn");

    QHBoxLayout *hlt_Icon=new QHBoxLayout;
    hlt_Icon->setMargin(0);
    hlt_Icon->setSpacing(0);
    hlt_Icon->addStretch(99);
    hlt_Icon->addWidget(aboutIcon,1);
    hlt_Icon->addStretch(99);

    QHBoxLayout *hlt_Text=new QHBoxLayout;
    hlt_Text->setMargin(0);
    hlt_Text->setSpacing(0);
    hlt_Text->addStretch(99);
    hlt_Text->addWidget(aboutText,1);
    hlt_Text->addStretch(99);

    QHBoxLayout *hlt_Ver=new QHBoxLayout;
    hlt_Ver->setMargin(0);
    hlt_Ver->setSpacing(0);
    hlt_Ver->addStretch(99);
    hlt_Ver->addWidget(aboutVersion_1,1);
    hlt_Ver->addSpacing(5);
    hlt_Ver->addWidget(aboutVersion_2,1);
    hlt_Ver->addStretch(99);

    QHBoxLayout *hlt_Mail = new QHBoxLayout;
    hlt_Mail->setMargin(0);
    hlt_Mail->setSpacing(0);
    hlt_Mail->addStretch(99);
    hlt_Mail->addWidget(aboutMail_1);
    hlt_Mail->addSpacing(5);
    hlt_Mail->addWidget(aboutMail_2);
    hlt_Mail->addStretch(99);


    QVBoxLayout *vlt_body=new QVBoxLayout;
    vlt_body->setMargin(0);
    vlt_body->setSpacing(0);
    vlt_body->addStretch(12);
    vlt_body->addLayout(hlt_Icon);
    vlt_body->addStretch(12);
    vlt_body->addLayout(hlt_Text);
    vlt_body->addStretch(12);
    vlt_body->addLayout(hlt_Ver);
    vlt_body->addStretch(12);
    vlt_body->addLayout(hlt_Mail);

    body->setLayout(vlt_body);

    QHBoxLayout *hlt3=new QHBoxLayout;//窗体
    hlt3->setMargin(0);
    hlt3->setSpacing(0);
//    hlt3->addSpacing(swa.shadow);
    hlt3->addWidget(body);
//    hlt3->addSpacing(swa.shadow);

    QVBoxLayout *vl=new QVBoxLayout;//总体
    vl->setMargin(0);
    vl->setSpacing(0);
    vl->addSpacing(swa.shadow);
    vl->addLayout(hlt2);
    vl->addLayout(hlt3);
    vl->addStretch(99);
    vl->addSpacing(swa.shadow);
    this->setLayout(vl);

}



void AboutWidget::showOrHide()
{
    if(this->isHidden())
    {
        this->show();
    }
    else
    {
        this->hide();
    }
}


void AboutWidget::ThemeChooseForWidget(const QString& str)
{

    if("ukui-dark" == str || "ukui-black" == str)
    {

        //样式表stylesheet//测试用border:1px solid red;
        QString bodyStyleSheet="QWidget{background-color:rgba(20, 20, 20, 1);border-bottom-left-radius:"+QString::number(local_swa.radius)+
                                "px;border-bottom-right-radius:"+QString::number(local_swa.radius)+"px;}";
        title->setStyleSheet("QWidget{background-color:rgba(20, 20, 20, 1);border-top-left-radius:"
                                 +QString::number(local_swa.radius)+"px;border-top-right-radius:"+QString::number(local_swa.radius)+"px;}");
        body->setStyleSheet(bodyStyleSheet);


        widgetClose->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                   "QPushButton:hover{background-color:rgba(240,64,52,1);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                   "QPushButton:pressed{background-color:rgba(215,51,53,1);border-image:url(:/data/close_p.png);border-radius:4px;font-size:14px;}");
     }
    else
    {

       //样式表stylesheet//测试用border:1px solid red;
       QString bodyStyleSheet="QWidget{background-color:rgba(255,255,255,1);border-bottom-left-radius:"+QString::number(local_swa.radius)+
                               "px;border-bottom-right-radius:"+QString::number(local_swa.radius)+"px;}";
       title->setStyleSheet("QWidget{background-color:rgba(255,255,255,1);border-top-left-radius:"
                                +QString::number(local_swa.radius)+"px;border-top-right-radius:"+QString::number(local_swa.radius)+"px;}");
       body->setStyleSheet(bodyStyleSheet);


       widgetClose->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-image:url(:/data/close_d.png);border-radius:4px;font-size:14px;}"
                                  "QPushButton:hover{background-color:rgba(240,64,52,1);border-image:url(:/data/close_h.png);border-radius:4px;font-size:14px;}"
                                  "QPushButton:pressed{background-color:rgba(215,51,53,1);border-image:url(:/data/close_p.png);border-radius:4px;font-size:14px;}");
    }

}

