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


  bool vedio_mode = false;
  bool vedio_start = false; //录像开启

signals:


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
private:
  QHBoxLayout *btnLayout;
  QSettings *set;

};

#endif // BUTTON_H
