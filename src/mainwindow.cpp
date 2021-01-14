#include "mainwindow.h"
#include <QApplication>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QDesktopWidget>
#include <QThread>
#include <QPoint>
#include <QTime>
#include "aboutwidget.h"
#include <QDesktopWidget>
#define NUMBER_LOAD 100   //加载数量
#define TABWINDOWWIDETH 80                   //窗口宽度
#define TABWINDOWHEIGHT 84                   //窗口高度
#define TABTITLEHEIGHT 42                    //标题栏高度
#define TABSHADOWWIDTH 6                     //阴影宽度
#define TABWIDGETRADIUS 6                    //窗口圆角
#define TABBUTTONRADIUS 6                    //按钮圆角
#define TABSHADOWALPHA 0.08                  //阴影透明度

#define ABOUTWINDOWWIDETH  420                 //窗口宽度
#define ABOUTWINDOWHEIGHT  316                 //窗口高度
#define ABOUTTITLEHEIGHT 42                    //标题栏高度
#define ABOUTSHADOWWIDTH 6                     //阴影宽度
#define ABOUTWIDGETRADIUS 6                    //窗口圆角
#define ABOUTBUTTONRADIUS 6                    //按钮圆角
#define ABOUTSHADOWALPHA 0.08                  //阴影透明度

//相册宽度
#define picture_width 270
int MainWindow::picture_number;
MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent)
{

    proc = new QProcess();
    setWindowTitle(tr("kylin-camera"));
    //从配置文件读取
    imagePath = setting->value("save_path").toString();
//    picture_number = setting->value("piacure_number").toInt();


    if(imagePath == "")
    {
        imagePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        QString locale = QLocale::system().name();
        if (locale == "zh_CN")
        {
          imagePath += QStringLiteral("/图片/麒麟摄像头/");
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
    dead_time_sec = 3;
    setCommonUI();

    //将上次的拍照和录像保存
    picture_number = setting->value("picture_number").toInt();
    picture_list = picture_setting->childKeys();

    iter = picture_list.rbegin();
//    if(picture_list.size() > NUMBER_LOAD)
    for(int num = 0;iter != picture_list.rend();iter++){
        //配置文件中的地址存在
        QString str = *iter;
        QString pictureName = picture_setting->value(str).toString();
        bool isVedio = isVedio_setting->value(str).toBool();
        qDebug()<< str + " : " + pictureName;
        if(QFile(pictureName).exists()){
            qDebug() << picture_number;
            if(num > NUMBER_LOAD) break;
            imageView(pictureName,isVedio);
            num++;
        }
        else{
            picture_setting->remove(str);
        }
    }

    watcher = new QFileSystemWatcher;
    watcher->addPath("/dev/");
    devRead = new DeviceRead;
    connect(devRead,&DeviceRead::finish,setPage,&SettingPage::change_item);
    connect(devRead,&DeviceRead::finish,camerapage,&CameraPage::timeEvent);
    //启动计时器，监听设备，
    connect(watcher,&QFileSystemWatcher::directoryChanged,devRead,[=](){
        //devRead = new DeviceRead;
        devRead->start();
    });
//    connect(devRead,&QFileSystemWatcher::directoryChanged,setPage,&SettingPage::change_item);
//    connect(watcher,&QFileSystemWatcher::directoryChanged,camerapage,&CameraPage::timeEvent);


#ifdef __V10__
    this->setStyleSheet("MainWindow{background-color:#000000;}");
    setWindowIcon(QIcon(":/image/camera-app@2x.png"));
#endif
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

}

MainWindow::~MainWindow()
{
    delete pTitleBar;
    delete btnPage;
    delete viewpage;
    delete setWid;
    delete camerapage;
    delete setPage;
}



//总体页面布局，设置公共组件连接槽函数
void MainWindow ::setCommonUI(){
#ifdef __V10__
    this->setWindowFlags(Qt::FramelessWindowHint);
#endif
    // 窗体透明
//    this->setAttribute(Qt::WA_TranslucentBackground, true);

    // 标题栏
    pTitleBar = new TitleBar;
    btnPage = new Button;
    viewpage = new PictureViewPage(this);
    setWid = new Setting(this);
    camerapage = new CameraPage(this);
    setPage = new SettingPage;

    setWid->hide();
    setPage->current_dir_lab->setText(imagePath);

    setPage->raise();

    StyleWidgetAttribute aboutWin(ABOUTWINDOWWIDETH,ABOUTWINDOWHEIGHT,0,ABOUTWIDGETRADIUS,ABOUTSHADOWWIDTH,ABOUTSHADOWALPHA,ABOUTTITLEHEIGHT);
    aboutWinWidget = new AboutWidget(aboutWin,tr("kylin-camera"));

    viewpage->setFixedWidth(picture_width);
    viewpage->hide();
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    //这里是主界面的未显示部分
    //显示界面布局
    //这里重构一下，将布局加到构造函数中
//    camerapage->setMinimumSize(736,414);
    camerapage->setMinimumSize(800,450);
    camerapage->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    //置顶按钮
    camerapage->laytop = new QPushButton;
//    laytop->raise();
    camerapage->laytop->setIcon(QIcon(":/image/top.png"));
    camerapage->laytop->setFlat(true);
    camerapage->laytop->setFixedSize(30,30);
    camerapage->laytop->move(this->camerapage->width() ,this->pTitleBar->height());


    QVBoxLayout *pLayout = new QVBoxLayout;
    mainLayout = new QHBoxLayout;
    pictureLayout = new QGridLayout;
    btnPage->setFixedHeight(48);
//    pictureLayout->addWidget(viewpage);
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
    this->move((QApplication::desktop()->width() - this->width())/2, (QApplication::desktop()->height() - this->height())/2);

    // 显示和隐藏功能列表
    connect(pTitleBar->funcListButton,SIGNAL(clicked(bool)),this,SLOT(funcListHandle(bool)));
    connect(btnPage->picture,SIGNAL(clicked(bool)),this,SLOT(pictureview(bool)));
    connect(pTitleBar->m_pMaximizeButton,SIGNAL(clicked(bool)),this,SLOT(setMaxWindow(bool)));
    connect(pTitleBar,&TitleBar::close,setPage,&SettingPage::close);
    //
    connect(btnPage->cheese, SIGNAL(clicked()), this, SLOT(clickPhoto()));
    connect(this,SIGNAL(click_vedio()),this,SLOT(vedioDisplay()));
    connect(btnPage->cheese_vedio, SIGNAL(clicked()), this, SLOT(clickStartRecord()));
//    connect(btnPage->restore,&QPushButton::clicked,this,&MainWindow::clickRestore);
    connect(btnPage->stop,&QPushButton::clicked,this,&MainWindow::clickPause);
    connect(btnPage->cheese_stop, SIGNAL(clicked()), this, SLOT(clickStopRecord()));
    connect(viewpage->deleteBtn,SIGNAL(clicked()),this,SLOT(delete_picture()));

    //item事件
    connect(viewpage->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemDoubleClicked(QListWidgetItem*)));
    connect(viewpage->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemclicked(QListWidgetItem*)));
    connect(viewpage->listWidget->verticalScrollBar(),&QScrollBar::valueChanged,this,&MainWindow::listWidgetUpdate);
    //设置事件
    connect(setPage,SIGNAL(dir_change()),this,SLOT(save_dir_change()));
    connect(setPage,&SettingPage::change_resolutions,camerapage,&CameraPage::change_resolution);
    connect(setPage,&SettingPage::change_dev,camerapage,&CameraPage::change_device);
    connect(setWid->set,&QPushButton::clicked,this,&MainWindow::settingPageShow);
//    connect(setWid->mirrorbtn,&SwitchButton::toggled,this,&MainWindow::mirror);
    connect(setWid->quit,&QPushButton::clicked,this,&MainWindow::quit);
    connect(camerapage->laytop,&QPushButton::clicked,this,&MainWindow::stayTop);
    connect(setWid->about,&QPushButton::clicked,this,&MainWindow::initAbout);
    connect(setWid->help,&QPushButton::clicked,this,&MainWindow::initHelp);
    connect(setWid->theme,&QPushButton::clicked,this,&MainWindow::thememenu);

}


void MainWindow::clickPause()
{
    camerapage->camera->camera_stop_record();

}

//void MainWindow::clickRestore()
//{
//    camerapage->camera->camera_capture_restore();
//}

//拍照
void MainWindow::clickPhoto()
{
    //正常拍照
    if(!setWid->delaybtn->m_bChecked){
        QString name=creatName();
        takePhoto(name,false);
        is_vedio = false;
        AlbumRead *albRear=new AlbumRead(imagePath+name+".jpg");
        connect(albRear,&AlbumRead::finish,this,&MainWindow::imageDisplay);
        albRear->start();
    }
    //延时拍摄
    //在计时器未触发时方可进入，当计时器触发时禁止拍照
    else if(!timer ||!timer->isActive()){

        //延时倒计时和计数器开启
        camerapage->dead_time = new QLabel(this->camerapage);
        camerapage->dead_time->move(this->camerapage->width()/2 -  camerapage->dead_time->width()/3,
                                    this->camerapage->height()/2 - (camerapage->dead_time->height()/1.5));
        camerapage->dead_time->setText("3");
        QFont font ;
        font.setPointSize(80);
        camerapage->dead_time->setFont(font);
    //    camerapage->dead_time->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        camerapage->dead_time->resize(100,100);
        QPalette pal;
        pal.setColor(QPalette::WindowText,Qt::white);
        camerapage->dead_time->setPalette(pal);
        camerapage->dead_time->raise();

        timer = new QTimer(this);
        is_vedio = false;
        Button::vedio_start = 1; //关闭录像切换功能
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
    if(camerapage->has_device){
        QString name =creatName();
        fileNameTemp=name;
        takePhoto(name,true);
        is_vedio = true;
        QString tmp=imagePath+name+".mp4";
        //调用录像函数
        camerapage->camera->camera_start_record(tmp.toLocal8Bit().data());

        //录像计时器
        camerapage->recorder_time = new QTimer(this);
        camerapage->recorder_time_label = new QLabel(this->camerapage);

//        QHBoxLayout *hlayout = new QHBoxLayout;
//        QVBoxLayout *vlayout = new QVBoxLayout;
//        camerapage->timeLabel = new QWidget;
//        vlayout->addSpacing(100);
//        vlayout->addWidget(camerapage->recorder_time_label);
//        hlayout->addSpacing(100);
//        hlayout->addLayout(vlayout);
//        hlayout->addSpacing(100);
//        camerapage->timeLabel->setLayout(hlayout);
//        camerapage->layout->addWidget(camerapage->timeLabel);

        //显示录像数字
        camerapage->recorder_time_label->show();
        camerapage->recorder_time_label->raise();
        camerapage->recorder_time->start(1000);
        connect(camerapage->recorder_time,&QTimer::timeout,this,&MainWindow::updateRecordTime);
        QString str = "00:00:00";
        camerapage->recorder_time_label->setText(str);
        camerapage->recorder_time_label->setStyleSheet(
                    "font-size: 14px;"
                    "font-family: Noto Sans CJK SC;"
                    "font-weight: 400;"
                    "line-height: 22px;"
                    "color: #FFFFFF;"
                    "letter-spacing: 50px;"
                    "opacity: 0.35;   "
                    );
        camerapage->recorder_time_label->resize(59,20);

        camerapage->recorder_time_label->move(this->camerapage->width() / 2 - camerapage->recorder_time_label->width() / 2 ,
                                              this->camerapage->height() - camerapage->recorder_time_label->height());
//    QFont font ;
//    font.setPointSize(14);
//    camerapage->recorder_time_label->setFont(font);
//    QPalette pal;
//    pal.setColor(QPalette::WindowText,Qt::white);
//    camerapage->recorder_time_label->setPalette(pal);

    }
}


//停止录像
void MainWindow::clickStopRecord()
{
    camerapage->camera->camera_stop_record();
    AlbumRead *albRear = new AlbumRead(imagePath+"."+fileNameTemp+".jpg");
    connect(albRear,&AlbumRead::finish,this,&MainWindow::imageDisplay);
    albRear->start();
    //录像时间停止
    camerapage->recorder_time->stop();
    camerapage->hour = 0;
    camerapage->min = 0;
    camerapage->sec = 0;
    delete camerapage->recorder_time_label;
}


//void MainWindow::changeEvent(QEvent *event){
//    setWid->hide();
//}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 反锯齿;
    painter.setPen(Qt::transparent);
    QWidget::paintEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete){
        delete_picture();
    }
}


//鼠标按下事件,收起设置菜单
void MainWindow::mousePressEvent(QMouseEvent *event){

    press = true;
    int x = event->x();
    int y = event->y();
    //在小窗口模式下，点击是否在设置区域内
    int in_setting = x > 437 && x < 696 && y > 42 && y < 244;
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    qDebug() << pButton;
    if(event->button() == Qt::LeftButton){
        m_start = event->globalPos();
    }
    if(event->button() == Qt::LeftButton && pTitleBar->m_setButtonPressed && !in_setting ||
        pButton == pTitleBar->m_pMaximizeButton)
    {
        setWid->hide();
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(!press || event->button() == Qt::RightButton) return;
    // 持续按住才做对应事件
//    if(pTitleBar->m_leftButtonPressed) {
//        将父窗体移动到父窗体原来的位置加上鼠标移动的位置：event->globalPos()-m_start
//        将鼠标在屏幕中的位置替换为新的位置
        this->move(event->globalPos() + this->geometry().topLeft() - m_start);
        m_start = event->globalPos();
//    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // 鼠标左键释放
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标状态
        pTitleBar->m_leftButtonPressed = false;
        press = false;
    }
}



void MainWindow::funcListHandle(bool){
    if(setWid->isHidden()){
        QPoint p = pTitleBar->funcListButton->geometry().bottomLeft();
        setWid->show();
        setWid->raise();
        //设置界面窗口大小暂时设置成魔数
//        setWid->geometry()
        setWid->setGeometry(p.x() - 130,p.y() + 4,160,288);
        setWid->setStyleSheet(
            "QWidget{border-radius:6px;background-color: #303033;}"
            "box-shadow: 0px 3px 16px rgba(0, 0, 0, 0.75);"
            "opacity: 1;"
        );
    }
    else{
        setWid->hide();
    }
}

void MainWindow::setMaxWindow(bool){
    if(pTitleBar->m_setButtonPressed){
        setWid->hide();
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
        int w = this->width() - picture_width;
        int h = this->height();
        QPoint point = this->mapToGlobal(QPoint(0,0));
        qDebug() << point;

        if(pTitleBar->m_maxButtonPressed){
            viewpage->hide();
            this->setMinimumSize(800,536);
         }
        else
        {
          viewpage->hide();
          this->layout()->setGeometry(QRect(point.x(),point.y(),800,536));
          this->setFixedSize(w,h);
          this->setMinimumSize(800,536);
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


//初始化相册时使用，从前往后插入图片
void MainWindow::imageView(QString filename,bool isVedio)
{
    QPixmap *pixmap = new QPixmap;
    if(!pixmap->load(filename))
    {
       qDebug() << "load error";
    }
    QPixmap fitPixmap= pixmap->scaled(120,90,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QListWidgetItem *imageItem = new QListWidgetItem;

    //录像模式标识显示在图片上


    if(isVedio){
        QImage imageB(":/image/video-x-generic-symbolic.svg");
        imageB = imageB.scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        QPainter imagepainter(&fitPixmap);  //新建画板
        imagepainter.setCompositionMode(QPainter::CompositionMode_SourceOver);   //设置重叠效果
        imagepainter.drawImage(90,60, imageB);
        imagepainter.end();
        qDebug() << "image painter";
    }

    imageItem->setIcon(QIcon(fitPixmap));
    imageItem->setStatusTip(filename);

    viewpage->listWidget->insertItem(0,imageItem);
//    viewpage->listWidget->addItem(imageItem);
    viewpage->listWidget->scrollToBottom();
    delete pixmap;
}


//将图片显示在listwidget上
void MainWindow::imageDisplay(QString filename)
{
    QPixmap *pixmap = new QPixmap;
    if(!pixmap->load(filename))
    {
       qDebug() << "load error";
    }
    QPixmap fitPixmap= pixmap->scaled(120,90,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QListWidgetItem *imageItem = new QListWidgetItem;

    //录像模式标识显示在图片上
    if(is_vedio || filename[0] == '.'){
        QImage imageB(":/image/video-x-generic-symbolic.svg");
        imageB = imageB.scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        QPainter imagepainter(&fitPixmap);  //新建画板
        imagepainter.setCompositionMode(QPainter::CompositionMode_SourceOver);   //设置重叠效果
        imagepainter.drawImage(90,60, imageB);
        imagepainter.end();
        //现在没有把录像的标志写到录像的图片中
        qDebug() << "image painter";
    }

    //在配置文件中存储拍照的路径
    picture_number++;
    picture_setting->setValue(QString::number(picture_number),filename);
    isVedio_setting->setValue(QString::number(picture_number),is_vedio);
    setting->setValue("picture_number",picture_number);

    imageItem->setIcon(QIcon(fitPixmap));
    imageItem->setStatusTip(filename);

    viewpage->listWidget->addItem(imageItem);
    viewpage->listWidget->scrollToBottom();
    delete pixmap;
}

//删除所选项
void MainWindow::delete_picture()
{

    if(index == viewpage->listWidget->count())
        index--;
    if(index == -1) return;
    //删除本地图片
    QString temp("rm -rf ");
    qDebug()<<index;
    temp.append(trueName(viewpage->listWidget->item(index)->statusTip()));
    startCommend(temp);
//    qDebug() << temp.at(temp.size() - 1);
    //删除录制视频时带的图片
    if(temp.at(temp.size() - 1) == '4'){
        startCommend("rm -rf " + viewpage->listWidget->item(index)->statusTip());
    }

    viewpage->listWidget->takeItem(index);
}




//将名字翻译成视频的文件类型
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
    QString fileName = trueName(item->statusTip());
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
    proc->startDetached(cmd);
}


void MainWindow::itemclicked(QListWidgetItem* item){
    index = viewpage->listWidget->row(item);
    qDebug() << index;
}


void MainWindow::listWidgetUpdate(int num){
    if(0 == num){
        loadPhoto();
    }
}

void MainWindow::loadPhoto(){

    for(int num = 0;iter != picture_list.rend();iter++){
        //配置文件中的地址存在
        QString str = *iter;
        QString pictureName = picture_setting->value(str).toString();
        bool isVedio = isVedio_setting->value(str).toBool();
        qDebug()<< str + " : " + pictureName;
        if(QFile(pictureName).exists()){
            qDebug() << picture_number;
            if(num > NUMBER_LOAD) break;
            imageView(pictureName,isVedio);
            num++;
        }
        else{
            picture_setting->remove(str);
        }
    }
}

//更改保存路径
void MainWindow::save_dir_change(){
    imagePath = setPage->current_dir;
    setting->setValue("save_path",imagePath);
    //  imagePath.append("/");
    qDebug() << "save dir change" << imagePath;
}

//计时器触发函数
void MainWindow::timeEvent()
{
    if(dead_time_sec_tmp >= dead_time_sec)
    {
        timer->stop();
        Button::vedio_start = 0; //开启录像切换功能
        dead_time_sec_tmp = 0;
        camerapage->dead_time->hide();
        QString name=creatName();
        takePhoto(name,false);
        AlbumRead *albRear = new AlbumRead(imagePath+name+".jpg");
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


void MainWindow::updateRecordTime(){
    int hour = camerapage->hour;
    int min = camerapage->min;
    int sec = camerapage->sec + 1;
    if(sec >= 60){
        if(++min >= 60) {
            hour++;
            min = 0;
        }
        sec = 0;
    }
    QString str_hour = (hour >= 10) ? QString::number(hour) : "0" + QString::number(hour);
    QString str_min = (min >= 10) ? QString::number(min) : "0" + QString::number(min);
    QString str_sec = (sec >= 10) ? QString::number(sec) : "0" + QString::number(sec);
    QString str = str_hour + ":" + str_min + ":" + str_sec;
    camerapage->recorder_time_label->setText(str);
    camerapage->hour = hour;
    camerapage->min = min;
    camerapage->sec = sec;
}

//显示设置界面
void MainWindow::settingPageShow(){

    setWid->hide();
    QPoint pos = QWidget::mapToGlobal(QPoint(250,150));
    setPage->Geometry(&pos);
    setPage->setWindowModality(Qt::ApplicationModal);
    setPage->show();
    setPage->update();
}

//点击连拍按钮
void MainWindow::clickBrust(){
    //打开连拍
    if(!Burst_mode){

    }
    else{

    }
}

void MainWindow::quit(){
    this->window()->close();
}

void MainWindow::initAbout(){
    QPoint pos = QWidget::mapToGlobal(QPoint(250,150));
    aboutWinWidget->setGeometry(QRect(pos.x(),pos.y(),0,0));
    aboutWinWidget->setWindowModality(Qt::ApplicationModal);
    aboutWinWidget->showOrHide();
}

void MainWindow::initHelp(){
    DaemonIpcDbus *ipcDbus = new DaemonIpcDbus();
    if(!ipcDbus->daemonIsNotRunning()){
        ipcDbus->showGuide("kylin-camera");
    }
}


void MainWindow::thememenu(){
    QPoint p = setWid->theme->geometry().topRight();
    setWid->themeMenu->exec(mapToGlobal(p));
    setWid->themeMenu->raise();
//    QMenu *themeMenu = new QMenu;
//    QActionGroup *themeMenuGroup = new QActionGroup(this);
//    QAction *autoTheme = new QAction(tr("Auto"),this);
//    themeMenuGroup->addAction(autoTheme);
//    themeMenu->addAction(autoTheme);
//    autoTheme->setCheckable(true);
//    QAction *lightTheme = new QAction(tr("Light"),this);
//    themeMenuGroup->addAction(lightTheme);
//    themeMenu->addAction(lightTheme);
//    lightTheme->setCheckable(true);
//    QAction *darkTheme = new QAction(tr("Dark"),this);
//    themeMenuGroup->addAction(darkTheme);
//    themeMenu->addAction(darkTheme);
//    darkTheme->setCheckable(true);
//    QList<QAction* > themeActions;
//    themeActions<<autoTheme<<lightTheme<<darkTheme;

////    autoTheme->setChecked(true);
//    actionTheme->setMenu(themeMenu);
//    menuButton->setMenu(m_menu);

//    connect(m_menu,&QMenu::triggered,this,&menuModule::triggerMenu);
//    initGsetting();
//    themeUpdate();
//    connect(themeMenu,&QMenu::triggered,this,&menuModule::triggerThemeMenu);

}
