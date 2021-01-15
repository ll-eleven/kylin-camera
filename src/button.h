#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QKeyEvent>
#include <QLayout>
#include <QWidget>
#include <QSettings>
#include "camerapage.h"
#include "pictureviewpage.h"


class Button : public QWidget
{
  Q_OBJECT
public:
    explicit Button(QWidget *parent = 0);
    ~Button();
    void CreatButton();


    QPushButton *capture;
    QPushButton *vedio;
    QPushButton *cheese;
    QPushButton *picture;
    QPushButton *Burst;  //连拍
    QPushButton *scale;
    QPushButton *voice;
    QPushButton *Setting;
    QPushButton *stop;
    QPushButton *cheese_vedio; // 录像开始
    QPushButton *cheese_stop;  // 录像结束
    QPushButton *restore;   //恢复

    static bool vedio_mode;
    static bool vedio_start; //录像开启
    static bool voice_mode;

signals:


public slots:

private slots:
    void capture_click();
    void vedio_click();
    void cheese_click();
    void picture_click();
    void Burst_click();
    void scale_click();
    void stop_click();
    void voice_click();
    void cheese_vedio_click();
    void cheese_stop_click();
    void restore_click();
    void focusInEvent();
private:

    QHBoxLayout *btnLayout;
    QSettings *set = new QSettings;
    bool Burst_mode = false;
    bool picturepage_show = false;
};

#endif // BUTTON_H
