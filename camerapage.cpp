#include "camerapage.h"
#include <QDebug>

CameraPage::CameraPage()
{

  camera = new QCamera(QCameraInfo::defaultCamera());
  lab = new QLabel(this);
//  camerainfo = new QCameraInfo;
  statusbar = new QStatusBar(this);
  viewfinder = new QCameraViewfinder(this);

  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->setMargin(0);
  layout->setSpacing(0);
  layout->addWidget(viewfinder);

  viewfinder->show();
  viewfinder->setAutoFillBackground(this);
  viewfinder->adjustSize();


  camera->setViewfinder(viewfinder);

  imageCapture = new QCameraImageCapture(camera);
  mediaRecorder = new QMediaRecorder(camera);
  mediaRecorder->setOutputLocation(QUrl::fromLocalFile(""));


  camera->setCaptureMode(QCamera::CaptureStillImage);

  camera->start();
  statusbar->setStyleSheet("color:#FFFFFF");

//  statusbar->setStyleSheet("background-color:#FFFFFF");
//  statusbar->setGeometry(0,0,50,50);
  statusbar->raise();
  //设置摄像头
  QCameraViewfinderSettings viewfinderSettings;
//  viewfinderSettings.setResolution(640, 480);
  viewfinderSettings.setMinimumFrameRate(30.0);
  viewfinderSettings.setMaximumFrameRate(30.0);

  camera->setViewfinderSettings(viewfinderSettings);

  connect(camera, SIGNAL(error(QCamera::Error)), this, SLOT(displayCameraError()));
//  connect(Button::cheese,SIGNAL(clicked()),imageCapture,SLOT(capture()));
//  connect(imageCapture,SIGNAL(imageCaptured(int,QImage)),this,SLOT(imageDisplay(int,QImage)));
//  connect(imageCapture, SIGNAL(imageSaved(int,QString)), this, SLOT(imageSavedSlot(int,QString)));

//  camera->captureMode(QCamera::CaptureVideo);
}

void CameraPage::displayCameraError(){
  qDebug() << "taida";
  lab->setText("未发现设备");
}

void CameraPage::setMediaRecorder(){

  camera->setCaptureMode(QCamera::CaptureVideo);
}
void CameraPage::setImageCapture(){

  camera->setCaptureMode(QCamera::CaptureStillImage);
  qDebug() << "image";
}
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
