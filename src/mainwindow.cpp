#include "mainwindow.h"
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QDesktopWidget>
#include <QThread>
#include <QPoint>
#include <QTime>


MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
{

  proc = new QProcess();

  //从配置文件读取
  imagePath = setting->value("save_path").toString();

  if(imagePath=="")
  {
      imagePath=QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
      QString locale = QLocale::system().name();
      if (locale == "zh_CN")
      {
          imagePath+=QStringLiteral("/图片/麒麟摄像头/");
      }
      else
      {
          imagePath+="/Pictures/kylin-camera/";
      }
      QDir dir(imagePath);
      if (!dir.exists()) {
          dir.mkpath(imagePath);
      }
      qDebug()<<"path:"<<imagePath;
  }

  //从配置文件读取，默认为3
  dead_time_sec=3;
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
    pTitleBar = new TitleBar(this);
    pTitleBar->setFixedHeight(42);

    btnPage = new Button;

    viewpage = new PictureViewPage;
    viewpage->setWindowFlags(Qt::FramelessWindowHint);

    setWid = new Setting(this);
    setWid->setStyleSheet(
        "QWidget{background-color: #303033;}"
        "box-shadow: 0px 3px 16px rgba(0, 0, 0, 0.75);"
        "opacity: 1;"
    );
    setWid->current_dir_lab->setText(imagePath);
    setWid->raise();
    setWid->setGeometry(QRect(476,40,220, 202));
    setWid->hide();


    viewpage->setFixedWidth(275);
    viewpage->hide();

    //显示界面布局
    camerapage = new CameraPage(this);
    camerapage->setMinimumSize(800,450);
    camerapage->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    camerapage->dead_time = new QLabel(this->camerapage);
    camerapage->dead_time->move(this->camerapage->width()/2 - 50, this->camerapage->height()/2 - 50);
    camerapage->dead_time->setText("3");
    QFont font ;
    font.setPointSize(80);
    camerapage->dead_time->setFont(font);
//    camerapage->dead_time->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    camerapage->dead_time->resize(100,100);
    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::white);
    camerapage->dead_time->setPalette(pal);
//    camerapage->dead_time->raise();
    camerapage->dead_time->hide();

//  pTitleBar->setFuncLabel(tr("标准"));


    QVBoxLayout *pLayout = new QVBoxLayout;
    mainLayout = new QHBoxLayout;
    pictureLayout = new QGridLayout;

    btnPage->setFixedHeight(48);
    pictureLayout->addWidget(viewpage);
    pLayout->setSpacing(0);
    pLayout->setMargin(0);
    pLayout->addWidget(pTitleBar);
    pLayout->addWidget(camerapage);
    pLayout->addWidget(btnPage);

    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addLayout(pLayout);
    mainLayout->addWidget(viewpage);

    this->setLayout(mainLayout);
    this->layout()->setSizeConstraint(QLayout::SetMinimumSize);
    //屏幕中央
    this->move((QApplication::desktop()->width() -this->width())/2, (QApplication::desktop()->height() - this->height())/2);
    // 显示和隐藏功能列表
    connect(pTitleBar->funcListButton,SIGNAL(clicked(bool)),this,SLOT(funcListHandle(bool)));
    connect(btnPage->picture,SIGNAL(clicked(bool)),this,SLOT(pictureview(bool)));


    //
    connect(btnPage->cheese, SIGNAL(clicked()), this, SLOT(clickPhoto()));
    connect(this,SIGNAL(click_vedio()),this,SLOT(vedioDisplay()));
    connect(btnPage->cheese_vedio, SIGNAL(clicked()), this, SLOT(clickStartRecord()));
//    connect(btnPage->cheese_vedio,SIGNAL(clicked()),this,SLOT(clickPhoto()));

    connect(btnPage->cheese_stop, SIGNAL(clicked()), this, SLOT(clickStopRecord()));
    connect(viewpage->deleteBtn,SIGNAL(clicked()),this,SLOT(delete_picture()));

    //item事件
    connect(viewpage->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemDoubleClicked(QListWidgetItem*)));
    connect(viewpage->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemclicked(QListWidgetItem*)));

    //设置事件
    connect(setWid,SIGNAL(dir_change()),this,SLOT(save_dir_change()));
    connect(setWid,SIGNAL(),this,SLOT());
//    connect(camerapage->mediaRecorder,SIGNAL(imagevedio()),this,SLOT());
//    connect(pTitleBar->m_pTopButton,SIGNAL(clicked(bool)),this,SLOT(stayTop()));

    pTitleBar->setStyleSheet("background-color:#000000;border-top-left-radius:6px");

}


void MainWindow::clickPause()
{
    camerapage->camera->camera_capture_pause();

}

void MainWindow::clickRestore()
{
    camerapage->camera->camera_capture_restore();
}

//拍照
void MainWindow::clickPhoto()
{
    //正常拍照
    if(!setWid->delaybtn->m_bChecked){
        QString name=creatName();
        takePhoto(name,false);
        AlbumRead *albRear=new AlbumRead(imagePath+name+".jpg");
        connect(albRear,&AlbumRead::finish,this,&MainWindow::imageDisplay);
        albRear->start();
    }
    //延时拍摄
    else{
        timer = new QTimer(this);
        connect(timer,&QTimer::timeout, this, &MainWindow::timeEvent);
        timer->start(1000);
        dead_time_sec_tmp = 0;
    }
}
QString MainWindow::creatName()
{
    QDateTime time= QDateTime::currentDateTime();
    return time.toString("yyyyMMdd_hhmmss")+"_"+QString::number(rand() % 10);
}


void MainWindow::takePhoto(QString name ,bool isvideo)
{
    QString path;
    path += imagePath;
    if(isvideo) path += ".";
    path += name;
    path += ".jpg";

    if(camerapage->has_device){
      camerapage->camera->camera_take_photo(path.toLocal8Bit().data());
    }
    if(isvideo)
    {
        //处理图片，将播放键的图片合成进去
    }
}


//录像
void MainWindow::clickStartRecord()
{
    QString name =creatName();
    fileNameTemp=name;
    takePhoto(name,true);
    QString tmp=imagePath+name+".mp4";
    if(camerapage->has_device){
      camerapage->camera->camera_start_record(tmp.toLocal8Bit().data());
    }
}


//停止录像
void MainWindow::clickStopRecord()
{
    camerapage->camera->camera_stop_record();
    AlbumRead *albRear=new AlbumRead(imagePath+"."+fileNameTemp+".jpg");
    connect(albRear,&AlbumRead::finish,this,&MainWindow::imageDisplay);
    albRear->start();

}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 反锯齿;
    painter.setPen(Qt::transparent);
    QWidget::paintEvent(event);
}


//鼠标按下事件,收起设置菜单
void MainWindow::mousePressEvent(QMouseEvent *event){

  int x = event->x();
  int y = event->y();
  //在小窗口模式下，点击是否在设置区域内
  int in_setting = x > 437 && x < 696 && y > 42 && y < 244;
  QPushButton *pButton = qobject_cast<QPushButton *>(sender());
  qDebug() << pButton;
  if(event->button() == Qt::LeftButton && pTitleBar->m_setButtonPressed && !in_setting ||
        pButton == pTitleBar->m_pMaximizeButton)
  {
    setWid->hide();
    pTitleBar->m_setButtonPressed = true;
  }
}

void MainWindow::funcListHandle(bool){

  if (setWid->isHidden()) {
      this->setWid->show();
      this->setWid->raise();
      pTitleBar->m_setButtonPressed = true;
  }
  else{
      this->setWid->hide();
      pTitleBar->m_setButtonPressed = false;
  }
}



//显示相册
void MainWindow::pictureview(bool){
    //打开相册
    if(this->viewpage->isHidden()){
        viewpage->show();
      }
    //隐藏相册
    else{
        int w = this->width() - 268;
        int h = this->height();
        QPoint point = this->mapToGlobal(QPoint(0,0));
        qDebug() << point;

        if(pTitleBar->m_maxButtonPressed){
            viewpage->hide();
            this->setMinimumSize(800,540);
         }
        else
        {
          viewpage->hide();
          this->layout()->setGeometry(QRect(point.x(),point.y(),800,540));
          this->setFixedSize(w,h);
          this->setMinimumSize(800,540);
          this->setMaximumSize(10086,10086);
        }
      }
}


void MainWindow::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    Q_UNUSED(fileName);
    qDebug() << imagePath;
}


//将图片显示在listwidget上
void MainWindow::imageDisplay(QString filename)
{
    QPixmap *pixmap=new QPixmap;
    if(!pixmap->load(filename))
    {
       qDebug() << "load error";
    }
    QPixmap fitPixmap= pixmap->scaled(120,90,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QListWidgetItem *imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon(fitPixmap));
    imageItem->setStatusTip(trueName(filename));
    qDebug()<<"==="<<trueName(filename);

    viewpage->listWidget->addItem(imageItem);
    delete pixmap;
}

QString MainWindow::trueName(QString name)
{
    QString tmp =name;
    for(int i=tmp.length()-1;i>=0;i--)
    {
        if(tmp.at(i)=='/')
        {
            if(tmp.at(i+1)!='.')
                return tmp;
             tmp=tmp.remove(i+1,1);
             tmp.chop(3);
             tmp+="mp4";
             return tmp;
        }
    }
    return tmp;
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

//打开录像或图片
void MainWindow::itemDoubleClicked(QListWidgetItem *item)
{
    //点击打开图片
    QString fileName=item->statusTip();
    qDebug()<< "fileName =" << fileName;
    QFileInfo dir(fileName);
    if(dir.exists())
    {
        QString temp("xdg-open ");
        temp.append(fileName);
//        startCommend(fileName);
        startCommend(temp);
        qDebug() << "cmd :  "<< temp;
    }

}


void MainWindow::startCommend(QString cmd)
{
//  system(cmd.toLatin1().data());
//    cmd.append("\n");
//  QStringList strL(cmd);
//    proc->start("xdg-open", strL);
    proc->startDetached(cmd);
//    proc->start(cmd);
    /*proc->write(cmd.toLatin1().data());*/
    /*proc->waitForFinished(); */


}
void MainWindow::itemclicked(QListWidgetItem* item){
  index = viewpage->listWidget->row(item);
}

//删除所选项
void MainWindow::delete_picture()
{
    if(index == viewpage->listWidget->count())
        index--;
    if(index == -1) return;
    //删除本地图片
    QString temp("rm -rf ");
    temp.append(trueName(viewpage->listWidget->item(index)->statusTip()));
    startCommend(temp);
    viewpage->listWidget->takeItem(index);
}


//更改保存路径
void MainWindow::save_dir_change(){
  imagePath = setWid->current_dir;
  setting->setValue("save_path",imagePath);
//  imagePath.append("/");
  qDebug() << "save dir change" << imagePath;
}



void MainWindow::timeEvent()
{
    if(dead_time_sec_tmp >= dead_time_sec)
    {
        timer->stop();
        dead_time_sec_tmp = 0;
        camerapage->dead_time->hide();
        QString name=creatName();
        takePhoto(name,false);
        AlbumRead *albRear=new AlbumRead(imagePath+name+".jpg");
        connect(albRear,&AlbumRead::finish,this,&MainWindow::imageDisplay);
        albRear->start();
        return;
    }
    else
    {
        QString str = QString::number(dead_time_sec - dead_time_sec_tmp);
        camerapage->dead_time->setText(str);
        camerapage->dead_time->show();
    }

    dead_time_sec_tmp++;
}
