#ifndef SETTING_H
#define SETTING_H
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QString>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QAction>
#include <QFileDialog>
#include <QSettings>
#include "switchbutton.h"

class Setting: public QWidget
{
  Q_OBJECT

public:
  Setting(QWidget *parent = 0);
//  ~Setting();
  QLabel *dirlab;
  QLabel *mirrorlab;
  QLabel *delaylab;
  QLabel *scalelab;
  QLabel *cameraDevicelab;
  QLabel *vedioDevicelab;
  QPushButton *dir;
  QPushButton *scale;
  QPushButton *cameraDevice;
  QPushButton *vedioDevice;
  SwitchButton *delaybtn;
  SwitchButton *mirrorbtn;
  QVBoxLayout *vlayout;

  QHBoxLayout *delayLayout;
  QHBoxLayout *mirrorLayout;
  QHBoxLayout *dirLayout;
  QHBoxLayout *scaleLayout;
  QHBoxLayout *cameraDeviceLayout;
  QHBoxLayout *vedioDeviceLayout;

  //当前路径
  QString current_dir;
  QLabel *current_dir_lab;

signals:
  void dir_change();
//  void scale_change();
public slots:
  void dir_click();
//  void scale_click();
//  void cameraDevice_click();
//  void vedioDevice_click();
//  void delay_click();
//  void mirror_click();
};

#endif // SETTING_H
