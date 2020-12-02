#ifndef CAMERAPAGE_H
#define CAMERAPAGE_H
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QMovie>
#include <QBoxLayout>
#include <QCameraViewfinder>
#include <QCamera>
#include <QCameraInfo>
#include <QPixmap>
#include <QStackedLayout>
#include <QMediaServiceCameraInfoInterface>
#include <QMediaService>
#include <QImage>
#include <QMessageBox>
#include <QLayout>
#include <QTimer>
#include <QTime>
#include <QCameraCaptureBufferFormatControl>
#include <QCameraImageCapture>
#include <QStatusBar>
#include <QMediaRecorder>
#include <QTimer>
#include "button.h"
#include "VideoDisplay.h"
#include "kylincamera_global.h"
#include "KylinCamera.h"

class CameraPage : public QWidget
{
  Q_OBJECT
public:
  explicit CameraPage(QWidget *parent = 0);
  QImage image;

  QPushButton *laytop;
  QPushButton *fullScreen;
  QPushButton *leftdown;
  QCameraInfo *camerainfo;

//  QCamera *camera;
  QCameraViewfinder *viewfinder;
  QMediaRecorder* mediaRecorder;

  QStatusBar *statusbar;  //录像时间
  QCameraImageCapture *imageCapture;


  KylinCamera *camera;
  VideoCapture *video;
  VideoDisplay *videoDisplay;
  
  QLabel *dead_time;
  QWidget *dead_widget;
  QTimer *time;
  bool has_device;
public slots:
  void updateRecordTime();
//  void setImageCapture();
//  void setMediaRecorder();
  void record();
  void stop();
  void pause();
  void displayCameraError();
  void timeEvent();
private:

  QLabel *lab;
};

#endif // CAMERAPAGE_H
