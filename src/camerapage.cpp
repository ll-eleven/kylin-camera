
#include "camerapage.h"
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include "unistd.h"
#include <sys/stat.h>
#include <string.h>
#include <QCameraInfo>
#include <QList>
#include <QString>


bool CameraPage::has_device = 0;
char* CameraPage::current_indevice = new char[128];
QList<QCameraInfo>* CameraPage::cameras = new QList<QCameraInfo>;
QList<QAudioDeviceInfo> * CameraPage::audios = new QList<QAudioDeviceInfo>;


CameraPage::CameraPage(QWidget *parent)
: QStackedWidget(parent)
{

    No_device = new QWidget;
    cameraViewPage = new QWidget;
    //读取摄像头文件,默认读取第一个摄像头设备
    *cameras = QCameraInfo::availableCameras();
    QString devname;
    this->addWidget(No_device);
    this->addWidget(cameraViewPage);
    //摄像头列表非空,选取第一个摄像头设备
    if(!cameras->empty()){
        devname = cameras->at(0).deviceName();
        creatCameraPage(devname.toLocal8Bit().data());
        this->setCurrentWidget(cameraViewPage);
    }
    //未接入摄像头设备
    else{
        displayCameraError();
    }
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

//摄像头未接入显示错误
void CameraPage::displayCameraError(){

    has_device = 0;
    widget1 = new QWidget;
    widget2 = new QWidget;
    No_device_icon = new QLabel(No_device);
    No_device_lab = new QLabel(No_device);
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    QHBoxLayout *hlayout1 = new QHBoxLayout;

    hlayout->addStretch(0);
    hlayout->addWidget(No_device_icon);
    hlayout->addStretch(0);
    hlayout->setMargin(0);
    hlayout1->addStretch(0);
    hlayout1->addWidget(No_device_lab);
    hlayout1->addStretch(0);
    hlayout1->setMargin(0);

    widget1->setLayout(hlayout);
    widget2->setLayout(hlayout1);
    layout->addStretch(10);
    layout->addWidget(widget1);
    layout->addWidget(widget2);
    layout->addStretch(10);
    No_device_icon->setPixmap(QPixmap(":/image/camera-disconnected.png"));
    No_device_lab->setText(tr("No device were found"));
    No_device_lab->setStyleSheet("color:#FFFFFF;"
                                 "width: 72px;"
                                 "height: 18px;"
                                 "font-size: 12px;"
                                 "font-family: Noto Sans CJK SC;"
                                 "font-weight: 400;"
                                 "line-height: 28px;"
                                 "opacity: 0.75;"
    );
//    No_device->move((this->width() / 2) - No_device->width() / 2 ,this->height() / 2 - No_device->height() );
    No_device->setLayout(layout);
    this->setCurrentWidget(No_device);

}




//初始化摄像头设备，和摄像头显示界面布局的初始化
void CameraPage::creatCameraPage(const char *in_devname){
    if(has_device)
    {
      delete layout;
      delete videoDisplay;
    }
    camera = new KylinCamera(cameraViewPage);
    layout = new QStackedLayout(cameraViewPage);

    V4l2DeviceInfo device_info;
    memset(&device_info,0X00,sizeof(V4l2DeviceInfo));
    memcpy(device_info.dev_path, in_devname, strlen(in_devname)+1);

    KylinCamera::enum_device(&device_info);
    camera->fourcc(KylinCamera::enum_device(&device_info));

    KylinCameraInfo camera_info;
    memset(&camera_info,0X00,sizeof(KylinCameraInfo));
    memcpy(camera_info.devname, in_devname, strlen(in_devname)+1);

//    qDebug() << "height:"<< device_info.fmt_supported[0].frm_sizes[0].frm_size.discrete.height << "\nwidth :"<< camera_info.width;
//    camera_info.format = V4L2_PIX_FMT_MJPEG;

    // 获取支持的格式
    for(TypePixFormats fmt : device_info.fmt_supported){
        qDebug ()<< "description : "  << fmt.frm_sizes_len;
        if(fmt.frm_sizes_len){
            for(auto a: fmt.frm_sizes){
                 //对于全局变量的准备
                if(a.frm_size.pixel_format != 0)
                    CurrentDeviceInfo::available_format = a.frm_size.pixel_format;
                 QPair<uint,uint> discrete;
                 discrete.first = a.frm_size.discrete.width;
                 discrete.second = a.frm_size.discrete.height;
                 if(discrete.first != 0 && discrete.second != 0){
                     CurrentDeviceInfo::available_size.push_back(discrete);
                 }
                 qDebug() << a.frm_size.discrete.width << a.frm_size.discrete.height;

                 for(auto b : a.frm_ivals){
                     if(b.index){

                         qDebug() << b.stepwise.min.denominator;
                     }
//                     qDebug() << b.stepwise.step.denominator;
                 }
            }
            //暂时就使用一个可用格式
            break;
        }
    }


    camera_info.format = CurrentDeviceInfo::available_format;
    camera_info.width = CurrentDeviceInfo::available_size.front().first;
    camera_info.height = CurrentDeviceInfo::available_size.front().second;
    CurrentDeviceInfo::current_size = CurrentDeviceInfo::current_size;
//    camera_info.fps = 30;
    qDebug()<<in_devname;
    videoDisplay = camera->create(this, &camera_info);
    strcpy(current_indevice,in_devname);

    //初始化声音设备
//    for( QAudioDeviceInfo &deviceInfo: QAudioDeviceInfo::availableDevices(QAudio::AudioInput))
//    {
//        if(deviceInfo.deviceName().contains("Camera"))
//        {
//            qDebug()<<"audio device:"<<deviceInfo.deviceName() ;
//            camera->camera_audio_init(deviceInfo);
//            break;
//        }
//        else
//        {
//             qDebug()<<deviceInfo.deviceName();
//        }
//    }

    videoDisplay->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    layout->setMargin(0);
    layout->addWidget(videoDisplay);

    cameraViewPage->setLayout(layout);
    this->setCurrentWidget(cameraViewPage);
    has_device = 1;

}



//设置分辨率
void CameraPage::change_resolution(QPair<uint, uint> resolution){
    KylinCameraInfo camerainfo;
    memset(&camerainfo,0X00,sizeof(KylinCameraInfo));
    memcpy(camerainfo.devname,current_indevice,strlen(current_indevice)+1);
//    camerainfo.format = V4L2_PIX_FMT_MJPEG;
    qDebug() <<  CurrentDeviceInfo::available_format <<  V4L2_PIX_FMT_MJPEG << V4L2_PIX_FMT_YUYV;
    camerainfo.format = CurrentDeviceInfo::available_format;
    camerainfo.width = resolution.first;
    camerainfo.height = resolution.second;
    camerainfo.fps = 30;

    camera->camera_set_param(&camerainfo);
}



//改变摄像头设备
void CameraPage::change_device(const char *in_device){
    KylinCameraInfo camerainfo;
    memset(&camerainfo,0X00,sizeof(KylinCameraInfo));
    memcpy(camerainfo.devname,in_device,strlen(in_device)+1);

    V4l2DeviceInfo device_info;
    memset(&device_info,0X00,sizeof(V4l2DeviceInfo));
    memcpy(device_info.dev_path, in_device, strlen(in_device)+1);

    // 获取摄像头支持的格式和分辨率
    for(TypePixFormats fmt : device_info.fmt_supported){
        qDebug ()<< "description : "  << fmt.frm_sizes_len;
        if(fmt.frm_sizes_len){
            for(auto a: fmt.frm_sizes){
                 //对于全局变量的准备
                if(a.frm_size.pixel_format != 0)
                    CurrentDeviceInfo::available_format = a.frm_size.pixel_format;

                 QPair<uint,uint> discrete;
                 discrete.first = a.frm_size.discrete.width;
                 discrete.second = a.frm_size.discrete.height;
                 //将可用的分辨率加入
                 if(discrete.first != 0 && discrete.second != 0){
                     CurrentDeviceInfo::available_size.push_back(discrete);
                 }
                 qDebug() << a.frm_size.discrete.width << a.frm_size.discrete.height;

                 for(auto b : a.frm_ivals){
                     if(b.index){
                         qDebug() << b.stepwise.min.denominator;
                     }
//                     qDebug() << b.stepwise.step.denominator;
                 }
            }
            //暂时就使用一个可用格式
            break;
        }
    }

    camerainfo.format =  CurrentDeviceInfo::available_format;
    camerainfo.format = V4L2_PIX_FMT_MJPEG;
    camerainfo.width = 1920;
    camerainfo.height = 1080;
    camerainfo.fps = 30;

    camera->camera_set_param(&camerainfo);
    strcpy(current_indevice,in_device);
}

//得到设备支持的格式
unsigned int getCameraFormat(const char *in_device){

}


void CameraPage::camera_set_param(KylinCameraInfo *device_info){

    camera->camera_set_param(device_info);
}

void CameraPage::updateRecordTime()
{
//    QString str = QString("Recorded %1 sec").arg(mediaRecorder->duration()/1000);
//    statusbar->showMessage(str);
}


//切换摄像头的主要函数
//设备文件发生变化时触发，有设备接入或者拔出
//正在使用的设备被拔出时，若有其他设备则切换其他设备，若无设备则显示无设备界面
void CameraPage::timeEvent()
{
    static int i = 0;
    *cameras = QCameraInfo::availableCameras();
    qDebug() << "call time : " << ++i;

    //之前有设备，并且当前设备被拔出,拔出的设备时当前使用设备,当前设备已不存在
    if(has_device && current_indevice && access(current_indevice,F_OK) != 0){
        //设备列表非空，更新当前设备
        if(!cameras->empty()){
            change_device(cameras->at(0).deviceName().toLocal8Bit().data());
            return;
        }
        //当前已无设备，已经将设备拔出，将原结构释放
        else{
            memset(current_indevice,0X00,strlen(current_indevice)) ;
            displayCameraError();
            has_device = 0;
            delete camera;
//            delete videoDisplay;
            delete layout;
            return;
        }
    }

    qDebug()<<"camerapage.cpp:258";
    //只有第一次发现设备是触发
    if(!has_device && !cameras->empty()){
        QString str = cameras->at(0).deviceName();
        qDebug() << str.toLocal8Bit().data();
//        current_indevice = NULL;
//        memset(current_indevice,0X00,strlen(current_indevice));
        strcpy(current_indevice, str.toLocal8Bit().data());
        qDebug()<<"camerapage.cpp:264";
        struct stat s_stat;

        if(access(current_indevice,F_OK) == 0 && has_device == 0)
        {
            int i = 0;
            while(1)
            {
             sleep(1);
             memset(&s_stat , 0x00 , sizeof(struct stat));
             int ret = stat(current_indevice , &s_stat);
             qDebug() <<"camerapage.cpp:271";
            //
             if(ret == -1)
             {
                 return;
             }
             if((s_stat.st_mode == (unsigned long)8624))
             {
                 qDebug()<<"camerapage.cpp:279";
                 creatCameraPage(current_indevice);
//                 change_device(current_indevice);
                 return ;
             }
            }
        }
        else
        {
            qDebug()<<"camerapage.cpp:289";

        }
    }
    else
    {
        qDebug()<<"camerapage.cpp:289";

    }
//    删除设备
//    else{

//    }
}
