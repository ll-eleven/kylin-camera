#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopServices>
#include "titlebar.h"
#include "mainwindow.h"
#include "settingpage.h"

TitleBar::TitleBar(QWidget *parent)
  : QWidget(parent)
{


    // 按钮初始化

    funcListButton = new QPushButton;
    m_pFuncLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton;
    m_pCloseButton = new QPushButton(this);

    m_maxButtonPressed = 0;
    //  funcListButton->setText("function");
    //  m_pMinimizeButton->setText("min");
    //  m_pCloseButton->setText("close");

    // 设置空间大小
    //  funcListButton->setFixedSize(30,30);
    m_pFuncLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_pMaximizeButton->setFixedSize(30,30);
    m_pMinimizeButton->setFixedSize(30,30);
    m_pCloseButton->setFixedSize(30,30);
    funcListButton->setFixedSize(30,30);


    icon = new QLabel;//图标
    icon->setPixmap(QPixmap::fromImage(QImage(":/image/camera-app@2x.png")));

    funcListButton->setIcon(QIcon::fromTheme("application-menu"));
    m_pMinimizeButton->setIcon(QIcon::fromTheme("window-minimize-symbolic"));
    m_pCloseButton->setIcon(QIcon::fromTheme("window-close"));
//    m_pCloseButton->setProperty("isWindowButton",0x2);
//    m_pCloseButton->setProperty("useIconHighlightEffect",0x8);
//    m_pCloseButton->setAutoRaise(true);
//    m_pMaximizeButton->setIcon(QIcon(":/image/max.png"));
    m_pMaximizeButton->setIcon(QIcon::fromTheme("window-maximize-symbolic"));

//    funcListButton->setAcceptDrops();
    funcListButton->setProperty("isWindowButton", 0x1);
    funcListButton->setProperty("useIconHighlightEffect", 0x2);
    funcListButton->setFlat(true);

    m_pMinimizeButton->setProperty("isWindowButton", 0x1);
    m_pMinimizeButton->setProperty("useIconHighlightEffect", 0x2);
    m_pMinimizeButton->setFlat(true);

    m_pCloseButton->setProperty("isWindowButton", 0x2);
    m_pCloseButton->setProperty("useIconHighlightEffect", 0x8);
    m_pCloseButton->setFlat(true);

    m_pMaximizeButton->setProperty("isWindowButton", 0x1);
    m_pMaximizeButton->setProperty("useIconHighlightEffect", 0x2);
    m_pMaximizeButton->setFlat(true);

    // 设置对象名
    m_pFuncLabel->setObjectName("whiteLabel");
    funcListButton->setObjectName("funcListButton");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");

    m_pFuncLabel->setText(tr("kylin-camera"));
//    m_pFuncLabel->setStyleSheet("color:#A6A6A6;font-size:14px;font-family:SourceHanSansCN-Regular;");
//    QString btnStyle = \
//                     "QPushButton{border-radius:4px;}"
//                     "QPushButton:hover{background-color:rgba(255,255,255,0.1);}"
//                     "QPushButton:pressed{background-color:rgba(255,255,255,0.15);}";
//    funcListButton->setStyleSheet(btnStyle);
//    m_pMinimizeButton->setStyleSheet(btnStyle);
//    m_pMaximizeButton->setStyleSheet(btnStyle);
//    m_pCloseButton->setStyleSheet("QPushButton{border-radius:4px;}QPushButton:hover{background-color:#F86457;}");

    // 设置按钮布局
    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addSpacing(8);
    pLayout->addWidget(icon);
    pLayout->addSpacing(8);
    pLayout->addWidget(m_pFuncLabel);
    pLayout->addStretch(0);
    pLayout->addWidget(funcListButton);
    //  pLayout->addSpacing(4);
    pLayout->addWidget(m_pMinimizeButton);
    //  pLayout->addSpacing(4);
    pLayout->addWidget(m_pMaximizeButton);
    //  pLayout->addSpacing(4);
    pLayout->addWidget(m_pCloseButton);
    pLayout->addSpacing(4);
    pLayout->setMargin(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    this->setFixedHeight(38);
    this->setLayout(pLayout);
    this->setObjectName("title");
//    this->setStyleSheet("TitleBar#title{background-color:#000000}");
    //  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    // 设置信号和槽函数

    connect(m_pMinimizeButton,&QPushButton::clicked,this,&TitleBar::onClicked);
    connect(m_pCloseButton,&QPushButton::clicked,this,&TitleBar::onClicked);
    connect(m_pMaximizeButton,&QPushButton::clicked,this,&TitleBar::onClicked);
    connect(funcListButton,&QPushButton::clicked,this,&TitleBar::onClicked);
}
TitleBar::~TitleBar()
{

}
//void TitleBar::setFuncLabel(QString label)
//{
//    this->m_pFuncLabel->setText(label);
//}

// 双击标题栏进行界面的最大化/还原
//void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);

//    emit m_pMaximizeButton->clicked();
//}


//按钮功能设置，和槽链接
void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if(pButton == funcListButton){
//          QDesktopServices::openUrl(QUrl::fromLocalFile(""));

          }
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pTopButton)
        {
        }
        else if(pButton == m_pMaximizeButton){
              //窗口最大化
              if(!m_maxButtonPressed){
                pWindow->showMaximized();
                emit MaxBtn_change();
               }

              else{
                  pWindow->showNormal();
                }
                m_maxButtonPressed = !m_maxButtonPressed;
        }
        else if (pButton == m_pCloseButton)
        {
            emit close();
            pWindow->close();
        }
        else if (pButton == funcListButton)
        {
            qDebug() << "funcListButton";
//            emit iconButtonSignal();
        }
    }
}
