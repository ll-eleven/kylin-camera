#ifndef CAMERAPAGE_H
#define CAMERAPAGE_H
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QLayout>
#include <QCamera>
#include <QCameraInfo>
#include <QAudioDeviceInfo>
#include <QPixmap>
#include <QStackedLayout>
#include <QMediaServiceCameraInfoInterface>
#include <QMediaService>
#include <QImage>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <QCameraCaptureBufferFormatControl>
#include <QCameraImageCapture>
#include <QStatusBar>
#include <QMediaRecorder>
#include <QTimer>
#include <QFileSystemWatcher>
#include <QStackedWidget>
#include <QApplication>
#include <QFileInfoList>
#include "currentdeviceinfo.h"
#include "button.h"
#include "VideoDisplay.h"
#include "kylincamera_global.h"
#include "KylinCamera.h"


class CameraPage : public QStackedWidget
{
    Q_OBJECT
public:
    CameraPage(QWidget *parent = 0);
    QImage image;
    //图像右上角按钮
    QPushButton *laytop;
    QPushButton *fullScreen;
    QPushButton *leftdown;
    QCameraInfo *camerainfo;

    QStatusBar *statusbar;  //录像时间
    QStackedLayout *layout;
//    QVBoxLayout *layout;
    //摄像头信息
    KylinCamera *camera;
    VideoCapture *video;
    VideoDisplay *videoDisplay;
    QFileInfoList video_info;

    QList<QCameraInfo> camerainfo_list;
    QCameraInfo camera_info;


    //倒计时
    QLabel *dead_time;
    QTimer *time;

    QWidget *timeLabel;
    QLabel *recorder_time_label;
    QTimer *recorder_time;
    int hour = 0;
    int min = 0;
    int sec = 0;
    //未发现摄像头
    QLabel *No_device_lab;
    QLabel *No_device_icon;

    //静态全局变量保存摄像头的状态，当前摄像头状态和现有的设备列表
    static bool has_device;
    static char* current_indevice;
    static QList<QCameraInfo> *cameras;
    static QList<QAudioDeviceInfo> *audios;
public slots:
    void updateRecordTime();
    //
    void displayCameraError();
    //时间信号
    void timeEvent();
    //未发现设备
    //  void No_find_device();
    //打开摄像头
    void creatCameraPage(const char *);
    //设置设备参数
    void camera_set_param(KylinCameraInfo *);
    //更改摄像头设备
    void change_device(const char *);
    //设置分辨率
    void change_resolution(QPair<uint,uint>);

private:
    //创建显示界面
    //未发现摄像头的两个组件
    QWidget *widget1;
    QWidget *widget2;
    //未发现摄像头界面
    QWidget *No_device;
    //摄像头显示界面
    QWidget *cameraViewPage;
    QLabel *lab;

};

#endif // CAMERAPAGE_H
