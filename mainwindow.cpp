#include "mainwindow.h"

#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QDesktopWidget>
#include <QThread>


MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
{
    setCommonUI();

    this->setStyleSheet("MainWindow{background-color:#000000;border-radius:6px}");

}

MainWindow::~MainWindow()
{

}


void MainWindow ::setCommonUI(){

    this->setWindowFlags(Qt::FramelessWindowHint);
    // 窗体透明
//    this->setAttribute(Qt::WA_TranslucentBackground, true);


    titleBarWid = new QWidget;
    titleBarWid->setObjectName("titleBarWid");
    // 标题栏
    pTitleBar = new TitleBar;
//    installEventFilter(pTitleBar);
    pTitleBar->setFixedHeight(50);
//    pTitleBar->setMinimumWidth(500);
    camerapage = new CameraPage;
    btnPage = new Button;
//    btnPage = new QWidget;
    viewpage = new PictureViewPage;
    set = new Setting(this);

    QVBoxLayout *funcListLayout = new QVBoxLayout();
    funcListLayout->addWidget(set);
    funcListLayout->addStretch();
    funcListLayout->setSpacing(0);
    funcListLayout->setMargin(0);

    setWid = new QWidget(this);
    setWid->setLayout(funcListLayout);
    setWid->setContentsMargins(0,0,0,0);
    setWid->setStyleSheet("background:#36363A;color:#FFFFFF;font-size:18px;border:none;border-radius:4px;");
    setWid->raise();
    setWid->setFixedHeight(420);
    setWid->setFixedWidth(170);
    setWid->setGeometry(QRect(0, 40, 20, 170));
    setWid->hide();

    camerapage->setMinimumSize(800,450);
    viewpage->setFixedWidth(268);

    camerapage->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//  pTitleBar->setFuncLabel(tr("标准"));


    QVBoxLayout *pLayout = new QVBoxLayout;
    mainLayout = new QHBoxLayout;
    pictureLayout = new QGridLayout;

    btnPage->setFixedHeight(55);
    pictureLayout->addWidget(viewpage);
    pLayout->setSpacing(0);
    pLayout->setMargin(0);
    pLayout->addWidget(pTitleBar);
    pLayout->addWidget(camerapage);
    pLayout->addWidget(btnPage);

//    pLayout->setGeometry(QRect(500,200,786, 628));

    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addLayout(pLayout);
    mainLayout->addLayout(pictureLayout);

    this->setLayout(mainLayout);
    // 显示和隐藏功能列表
    connect(pTitleBar->funcListButton,SIGNAL(clicked(bool)),this,SLOT(funcListHandle(bool)));
    connect(btnPage->picture,SIGNAL(clicked(bool)),this,SLOT(pictureview(bool)));


    connect(btnPage->vedio,SIGNAL(clicked(bool)),camerapage,SLOT(setMediaRecorder()));
    connect(btnPage->capture,SIGNAL(clicked(bool)),camerapage,SLOT(setImageCapture()));

    connect(btnPage->cheese,SIGNAL(clicked()),camerapage->imageCapture,SLOT(capture()));
    connect(camerapage->imageCapture,SIGNAL(imageCaptured(int,QImage)),this,SLOT(imageDisplay(int,QImage)));
    connect(camerapage->imageCapture,SIGNAL(imageSaved(int,QString)),this,SLOT(imageSaved(int,QString)));

    //录像模式

    connect(btnPage->cheese_vedio,SIGNAL(clicked()),camerapage,SLOT(record()));
    connect(btnPage->stop,SIGNAL(clicked(bool)),camerapage,SLOT(pause()));
    connect(btnPage->cheese_stop,SIGNAL(clicked()),camerapage,SLOT(stop()));

//    connect(camerapage->mediaRecorder,SIGNAL(imagevedio()),this,SLOT());



//    connect(pTitleBar->m_pTopButton,SIGNAL(clicked(bool)),this,SLOT(stayTop()));

    pTitleBar->setStyleSheet("background-color:#000000;border-top-left-radius:6px");
//    btnPage->setStyleSheet("background-color:#000000");

}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 反锯齿;
    painter.setPen(Qt::transparent);
    QWidget::paintEvent(event);
}


void MainWindow::funcListHandle(bool){

  if (setWid->isHidden()) {
      //        this->setFuncListUi();
      this->setWid->show();
  }
  else {
      this->setWid->hide();
  }
}


//void MainWindow::funcListItemClicked(QListWidgetItem* item)
//{
//    QString label = item->text().trimmed();
//    this->funcListWid->hide();

//    if (label != this->pTitleBar->m_pFuncLabel->text()) {
//        this->pTitleBar->setFuncLabel(label);

//        if (label == "路径") {

//            mainLayout->removeWidget(ButtonWid);

//            this->ButtonWid->close();

//            setStandardUi();
//            changeCalculatorUi();
//        }
//        else if (label == "延迟拍照") {

//            mainLayout->removeWidget(ButtonWid);

//            this->ButtonWid->close();

//            setScientificUi();
//            changeCalculatorUi();
//        }
//        else if (label == "声音") {

//            mainLayout->removeWidget(outputWid);
//            mainLayout->removeWidget(ButtonWid);

//            this->outputWid->close();
//            this->ButtonWid->close();

//            setToolUi();
//            changeToolUi();
//        }
//    }
//}

void MainWindow::pictureview(bool){

    if(this->viewpage->isHidden()){
        viewpage->show();
      }
    else{
        viewpage->hide();
      }
}
void MainWindow::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    Q_UNUSED(fileName);
}


void MainWindow::imageDisplay(int i,QImage image)
{
//    qDebug() << "fdsgvfdbg";
    QPixmap pixmap = QPixmap::fromImage(image);
    QPixmap fitPixmap= pixmap.scaled(120,90,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QListWidgetItem *imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon(fitPixmap));

    viewpage->listWidget->addItem(imageItem);
//    connect();

}

void MainWindow::stayTop()
{
    if (winFlags == NULL) {
        winFlags = windowFlags();
//        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
        show();
    }
    else {
        winFlags = NULL;
        this->raise();
        setWindowFlags(Qt::FramelessWindowHint);
        show();
    }
}
