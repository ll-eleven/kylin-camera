#include "settingpage.h"
#include <QDebug>
#include <QSettings>
#include <QStandardPaths>
#include <QMessageBox>
#include <QErrorMessage>
#include "currentdeviceinfo.h"
#include "unistd.h"
bool SettingPage::press = false;
int SettingPage::dev_change = 1;
SettingPage::SettingPage()

{

#ifdef __V10__
    this->setStyleSheet("{background-color:#000000;}");
#endif

    this->hide();
    this->setWindowTitle(tr("setting"));
//    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    this->raise();
    init_ui();
    change_item();
}

void SettingPage::Geometry(QPoint *pos){
    this->setGeometry(pos->x(),pos->y(),0,0);
    this->setFixedSize(340,238);
}


//设置ui
void SettingPage::init_ui(){
//    this->setAttribute(Qt::WA_StyledBackground);
//    setting = new QSettings;
    dirlab = new QLabel;
    scalelab = new QLabel;
    cameraDevicelab = new QLabel;
//    vedioDevicelab = new QLabel;

    cameraDevice = new QComboBox(this);
//    vedioDevice = new QComboBox(this);
    dir = new QPushButton(this);
    scale = new QComboBox(this);
    confirm = new QPushButton;
    cancel = new QPushButton;


    vlayout = new QVBoxLayout;
    dirLayout = new QHBoxLayout;
    scaleLayout = new QHBoxLayout;
    cameraDeviceLayout = new QHBoxLayout;
//    vedioDeviceLayout = new QHBoxLayout;
    btnLayout = new QHBoxLayout;

    QHBoxLayout *dirbtnLayout = new QHBoxLayout;

    current_dir_lab = new QLabel;
    current_cameraDev = new QLabel;
    current_vedioDev = new QLabel;
    QString combobox_style = "QComboBox::drop-down {subcontrol-origin: paddingsubcontrol-position: top right;"
                             "width: 15px;border-radius: 4px;}";
//    vedioDevice->setStyleSheet(combobox_style);
    cameraDevice->setStyleSheet(combobox_style);
    scale->setStyleSheet(combobox_style);
    current_dir_lab->setStyleSheet(
          "font-size: 12px;"
          "font-family: Noto Sans CJK SC;"
          "font-weight: 400;"
          "line-height: 14px;"
          "opacity: 1;"
          );
//    current_dir_lab->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    dirlab->setText(tr("The image path"));
    scalelab->setText(tr("The image scale"));
    cameraDevicelab->setText(tr("Camera device"));
//    vedioDevicelab->setText(tr("Sound device"));
    QString btnStyle = \
        "width: 204px;"
        "height: 30px;"
        "opacity: 1;"
        "border-radius: 4px;";

    QString labStyle = \
        "font-size: 14px;"
        "font-family: Noto Sans CJK SC;"
        "font-weight: 400;"
        "line-height: 32px;"
        "opacity: 1;";

    dirlab->setStyleSheet(labStyle);
    scalelab->setStyleSheet(labStyle);
    cameraDevicelab->setStyleSheet(labStyle);
//    vedioDevicelab->setStyleSheet(labStyle);

    dir->setStyleSheet(btnStyle);
    cameraDevice->setStyleSheet(btnStyle);
//    vedioDevice->setStyleSheet(btnStyle);
    scale->setStyleSheet(btnStyle);
    confirm->setText(tr("confirm"));
    cancel->setText(tr("cancel"));


    //保存用户配置
//    scale->setCurrentIndex(theme_setting->value("scale").toInt());


//    if(setting->value("scale").toInt()){
//        qDebug () << "settingpage.cpp:103" << "scale setting :" << setting->value("scale").toInt();

//    }
    //设置按钮布局
    scaleLayout->addSpacing(8);
    scaleLayout->addWidget(scalelab);
    scaleLayout->addWidget(scale);
    scaleLayout->setMargin(0);

//    vedioDeviceLayout->addSpacing(8);
//    vedioDeviceLayout->addWidget(vedioDevicelab);
//    vedioDeviceLayout->addWidget(vedioDevice);
//    vedioDeviceLayout->setMargin(0);


    QLabel *icon = new QLabel;
    icon->setPixmap(QPixmap::fromImage( QImage((":/image/document-open-symbolic.png"))));

    dirbtnLayout->addWidget(current_dir_lab);
    dirbtnLayout->addStretch(99);
    dirbtnLayout->addWidget(icon);
    dirbtnLayout->setMargin(0);
    dir->setLayout(dirbtnLayout);

    dirLayout->addSpacing(8);
    dirLayout->addWidget(dirlab);
    dirLayout->addStretch(10);
    dirLayout->addWidget(dir);
    dirLayout->setMargin(0);

    cameraDeviceLayout->addSpacing(8);
    cameraDeviceLayout->addWidget(cameraDevicelab);
//    cameraDeviceLayout->addWidget(current_cameraDev);
    cameraDeviceLayout->addWidget(cameraDevice);
    cameraDeviceLayout->setMargin(0);
//    cameraDevice->setCurrentText("wufang");

    btnLayout->addSpacing(99);
    btnLayout->addWidget(cancel);
    btnLayout->addWidget(confirm);


    vlayout->addLayout(dirLayout);
    vlayout->addLayout(scaleLayout);
    vlayout->addLayout(cameraDeviceLayout);
//    vlayout->addLayout(vedioDeviceLayout);
    vlayout->addLayout(btnLayout);

    this->setLayout(vlayout);
//  lineedit->setClearButtonEnabled(setClearButtonEnabled(true);

    cameraDevice->setDuplicatesEnabled(1);
//    vedioDevice->setDuplicatesEnabled(1);

    connect(dir,&QPushButton::clicked,this,&SettingPage::dir_click);
    connect(this,&SettingPage::change_dev,this,&SettingPage::change_cameraDevice);
    connect(confirm,&QPushButton::clicked,this,&SettingPage::confirm_click);
    connect(cancel,&QPushButton::clicked,this,&SettingPage::cancel_click);

}


void SettingPage::close(){
    this->window()->close();
}


//当设备有变化时更新设备列表，
//加入设备到device选项中
void SettingPage::change_item(){
    //添加摄像头设备
   //由于读取设备文件需要时间,这里开一个线程等待设备读取
//    sleep(1);
    static int a = 1;
    cameraDevice->clear();
//    vedioDevice->clear();
    qDebug()<< "setting.cpp:168";
    qDebug()<< "call time " << a++;
    *CameraPage::cameras = QCameraInfo::availableCameras();
    cameraDevice->setDuplicatesEnabled(1);
    //将读到的设备加到设置列表中
    foreach(const QCameraInfo &cameraInfo,*CameraPage::cameras){
        if(cameraDevice)
            cameraDevice->addItem(cameraInfo.description());
        qDebug() << "device : " << cameraInfo.deviceName();
        if(!camera_name2dev.count(cameraInfo.description())){
            camera_name2dev[cameraInfo.description()] = cameraInfo.deviceName();
        }
    }

    //添加录音设备
//    *CameraPage::audios = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
//    foreach(const QAudioDeviceInfo &audioInfo,*CameraPage::audios){
////        qDebug() << "vedio device "<<audioInfo.deviceName() << "\n";
//        if(audioInfo.deviceName().contains("Camera")){
//            vedioDevice->addItem(audioInfo.deviceName());
//        }
//    }
    CameraPage::cameras->clear();
    CameraPage::audios->clear();
}



//
void SettingPage::change_cameraDevice(const char *dev_name){

}


void SettingPage::dir_click(){

    current_dir = QFileDialog::getExistingDirectory(nullptr,tr("Select the directory"),"/home",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString first = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    if(QDir(current_dir).exists() && current_dir != "" && current_dir.contains(first,Qt::CaseSensitive)){
        current_dir.append('/');
        current_dir_lab->setText(current_dir);
        qDebug() << "current_dir"<< current_dir;
        emit dir_change();
        return;
    }
    if(QDir(current_dir).exists() && current_dir != "" ){
        QMessageBox::warning(this,tr("error"),tr("have no permissions !?"));
    }
}


void SettingPage::confirm_click(){
    //设置摄像头
    qDebug()<< CameraPage::current_indevice  << camera_name2dev[cameraDevice->currentText()];

    //切换设备
    if(CameraPage::current_indevice != camera_name2dev[cameraDevice->currentText()]){
        QString text = cameraDevice->currentText();
        QString str = camera_name2dev[text];
        qDebug() << text << " " << str;
        dev_change = 1;
        emit change_dev(str.toLocal8Bit().data());
    }

    //切换分辨率
    if(theme_setting->value("scale").toInt() != scale->currentIndex()){
        emit change_resolutions(CurrentDeviceInfo::available_size[scale->currentIndex()]);
        theme_setting->setValue("scale",scale->currentIndex());
        qDebug() << "settingpage.cpp:250 " <<  theme_setting->value("scale").toInt();
    }

    cancel_click();
}

void SettingPage::cancel_click(){
    this->window()->close();
}

void SettingPage::mousePressEvent(QMouseEvent *event){
    press = true;
    if(event->button() == Qt::LeftButton){
        m_start = event->globalPos();
    }
}

void SettingPage::mouseMoveEvent(QMouseEvent *event)
{
    if(!press) return;
    // 持续按住才做对应事件
//    if(pTitleBar->m_leftButtonPressed) {
//        将父窗体移动到父窗体原来的位置加上鼠标移动的位置：event->globalPos()-m_start
//        将鼠标在屏幕中的位置替换为新的位置
        this->move(event->globalPos() + this->geometry().topLeft() - m_start);
        m_start = event->globalPos();
//    }
}

void SettingPage::mouseReleaseEvent(QMouseEvent *event)
{
    // 鼠标左键释放
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标状态
        press = false;
    }
}

//更新设备信息
void SettingPage::update(){
    if(dev_change){
        scale->clear();
        for(auto p : CurrentDeviceInfo::available_size){
            QString str;
            str = QString::number(p.first) + "x" + QString::number(p.second);
            qDebug () << str;
            scale->addItem(str);
        }
        auto Size =  CurrentDeviceInfo::current_size;
        scale_str = QString::number(Size.first) + "x" + QString::number(Size.second);
        dev_change = 0;
    }
    scale->setCurrentIndex(theme_setting->value("scale").toInt());
    qDebug() << theme_setting->value("scale").toInt();

}
