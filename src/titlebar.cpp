#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopServices>
#include "titlebar.h"
#include "mainwindow.h"


TitleBar::TitleBar(QWidget *parent)
  : QWidget(parent)
{
  this->setFixedHeight(38);

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
  m_pFuncLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  m_pMaximizeButton->setFixedSize(30,30);
  m_pMinimizeButton->setFixedSize(30,30);
  m_pCloseButton->setFixedSize(30,30);
  funcListButton->setFixedSize(30,30);


  icon = new QLabel;//图标
  icon->setPixmap(QPixmap::fromImage(QImage(":/image/Screenshot@2x.png")));
  funcListButton->setIcon(QIcon(":/image/funclist.png"));
//  m_pTopButton->setIcon(QIcon(":/image/top.png"));
  m_pMinimizeButton->setIcon(QIcon(":/image/min.png"));
  m_pCloseButton->setIcon(QIcon(":/image/close.png"));
  m_pMaximizeButton->setIcon(QIcon(":/image/max.png"));
  m_pMinimizeButton->setIconSize(QSize(25, 25));

  // 设置对象名
  m_pFuncLabel->setObjectName("whiteLabel");
  funcListButton->setObjectName("funcListButton");
  m_pMinimizeButton->setObjectName("minimizeButton");
  m_pMaximizeButton->setObjectName("maximizeButton");
  m_pCloseButton->setObjectName("closeButton");

  m_pFuncLabel->setText(tr("kylin-camera"));
  m_pFuncLabel->setStyleSheet("color:#A6A6A6;font-size:14px;font-family:SourceHanSansCN-Regular;");
  QString btnStyle = /*"QPushButton{background-color:#FFFFFF}"*/
                     "QPushButton{border-radius:4px;}"
                     "QPushButton:hover{background-color:rgb(180,180,180);}"
                     "QPushButton:pressed{background-color:rgb(180,180,180);}";
  funcListButton->setStyleSheet(btnStyle);
  m_pMinimizeButton->setStyleSheet(btnStyle);
  m_pMaximizeButton->setStyleSheet(btnStyle);
  m_pCloseButton->setStyleSheet("QPushButton{border-radius:4px;}QPushButton:hover{background-color:red;}");

  // 设置按钮布局
  QHBoxLayout *pLayout = new QHBoxLayout(this);
  pLayout->addWidget(icon);
  pLayout->addSpacing(5);
  pLayout->addWidget(m_pFuncLabel);
  pLayout->addSpacing(10);
  pLayout->addWidget(funcListButton);
  pLayout->addWidget(m_pMinimizeButton);
  pLayout->addWidget(m_pMaximizeButton);
  pLayout->addWidget(m_pCloseButton);
  pLayout->setSpacing(0);
  pLayout->setContentsMargins(10, 0, 10, 0);

  this->setLayout(pLayout);
  this->setStyleSheet("background-color:rgba(0,0,0,0.7)");
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
//            pWindow->parentWidget()->parentWidget()->parentWidget()->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//            pWindow->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        }
        else if(pButton == m_pMaximizeButton){

              if(!m_maxButtonPressed){
                pWindow->showMaximized();
                }
              else{
                  pWindow->showNormal();
                }
                m_maxButtonPressed = !m_maxButtonPressed;
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
        else if (pButton == funcListButton)
        {
            qDebug() << "funcListButton";
//            emit iconButtonSignal();
        }
    }
}
