#include "camerapage.h"
#include <QDebug>

#include "unistd.h"
CameraPage::CameraPage(QWidget *parent)
: QWidget(parent)
{


    //倒计时数字


//    dead_widget->setGeometry(0,0,this->width(),this->height());
//    hlayout->addSpacing(100);
//    hlayout->addWidget(dead_time);
//    hlayout->addSpacing(100);
//    dead_widget->setLayout(hlayout);



    const char *in_devname = "/dev/video0";
    V4l2DeviceInfo device_info;

    if(access(in_devname,F_OK) == 0){
      camera = new KylinCamera(this);
      memset(&device_info,0X00,sizeof(V4l2DeviceInfo));
      memcpy(device_info.dev_path, in_devname, strlen(in_devname));
//      KylinCamera::enum_device(&device_info);
//      camera->fourcc(KylinCamera::enum_device(&device_info));
      KylinCameraInfo camera_info;
      memset(&camera_info,0X00,sizeof(KylinCameraInfo));

      memcpy(camera_info.devname, in_devname, strlen(in_devname));
      camera_info.format = V4L2_PIX_FMT_MJPEG;
      camera_info.width = 640;
      camera_info.height = 480;
      camera_info.fps = 30;
      videoDisplay = camera->create(this, &camera_info);
      videoDisplay->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

//      QHBoxLayout *layout = new QHBoxLayout(this);
      QStackedLayout *stackedlayout = new QStackedLayout(this);
      stackedlayout->setStackingMode(QStackedLayout::StackAll);
      stackedlayout->setMargin(0);
      stackedlayout->setSpacing(0);
      stackedlayout->setGeometry(QRect(0,100,500,500));
      stackedlayout->addWidget(videoDisplay);


//      camera->camera_set_param()

//      QVBoxLayout *layout = new QVBoxLayout;
//      layout->addLayout(stackedlayout);
    }
    //未接入设备，关闭应用
    else{
        QMessageBox::question(this,tr("No devices were found"),tr("No devices were found"),0);
//        exit(-1);
      }
//  ui->verticalLayout->addWidget(videoDisplay);

//  connect(ui->restoreButton, SIGNAL(clicked()), this, SLOT(clickRestore()));
//  connect(ui->resumeButton, SIGNAL(clicked()), this, SLOT(clickPause()));
//  connect(ui->setButton, SIGNAL(clicked()), this, SLOT(clickSet()));
//  connect(ui->photoButton, SIGNAL(clicked()), this, SLOT(clickPhoto()));
//  connect(ui->recordStartButton, SIGNAL(clicked()), this, SLOT(clickStartRecord()));
//  connect(ui->recordStopButton, SIGNAL(clicked()), this, SLOT(clickStopRecord()))
}

void CameraPage::displayCameraError(){
//  qDebug() << "taida";
  lab->setText("未发现设备");
}

//void CameraPage::setMediaRecorder(){
//  camera->setCaptureMode(QCamera::CaptureVideo);
//}

//void CameraPage::setImageCapture(){
//  camera->setCaptureMode(QCamera::CaptureStillImage);
//  qDebug() << "image";
//}

 void CameraPage::pause(){
  mediaRecorder->pause();
}
void CameraPage::stop(){
  mediaRecorder->stop();
}
void CameraPage::record(){
  mediaRecorder->record();
  updateRecordTime();
}
void CameraPage::updateRecordTime()
{
    QString str = QString("Recorded %1 sec").arg(mediaRecorder->duration()/1000);
    statusbar->showMessage(str);
}
