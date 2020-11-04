#ifndef SETTING_H
#define SETTING_H
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include "switchbutton.h"
class Setting: public QWidget
{
public:
  Setting(QWidget *parent = 0);

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
};

#endif // SETTING_H
