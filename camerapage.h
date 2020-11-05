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
#include <QMediaServiceCameraInfoInterface>
#include <QMediaService>
#include <QImage>
#include <QLayout>
#include <QCameraCaptureBufferFormatControl>
#include <QCameraImageCapture>
#include <QStatusBar>
#include <QMediaRecorder>
#include "button.h"

class CameraPage : public QWidget
{
  Q_OBJECT
public:
  explicit CameraPage();
  QImage image;

  QPushButton *laytop;
  QPushButton *fullScreen;
  QPushButton *leftdown;
  QCameraInfo *camerainfo;
  QCamera *camera;
  QCameraViewfinder *viewfinder;
  QMediaRecorder* mediaRecorder;
  QStatusBar *statusbar;  //录像时间
  QCameraImageCapture *imageCapture;
public slots:
  void updateRecordTime();
  void setImageCapture();
  void setMediaRecorder();
  void record();
  void stop();
  void pause();
  void displayCameraError();
private:

  QLabel *lab;
};

#endif // CAMERAPAGE_H
