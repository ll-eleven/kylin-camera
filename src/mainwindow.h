#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QKeyEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QListWidget>
#include <QStackedWidget>
#include <QTime>
#include <QByteArray>
#include <unistd.h>
#include <QMenu>
#include <QTimer>
#include <QSettings>

#include "titlebar.h"
#include "widgetstyle.h"
#include "button.h"
#include "camerapage.h"
#include "pictureviewpage.h"
#include "setting.h"
#include "VideoDisplay.h"
#include "kylincamera_global.h"
#include "KylinCamera.h"

#include <QDateTime>
#include <QStandardPaths>
#include <QPixmap>
#include "albumread.h"
#include <QProcess>
class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void setCommonUI();
  void stayTop();
  void paintEvent(QPaintEvent *event);
  void funcListItemClicked(QListWidgetItem* item);

  void setbutton();
  void setcamerapage();
  void setpicturepage();



  QPoint temp;
  bool settingShow = false;

signals:
  void click_vedio();
  void click_picture();
private slots:
  void takePhoto(QString name, bool isvideo);
  QString creatName();
  QString trueName(QString name);
  void startCommend(QString cmd);

  void clickPause();
  void clickRestore();
  void clickPhoto();
  void clickStartRecord();
  void clickStopRecord();
  void itemclicked(QListWidgetItem*);
  void itemDoubleClicked(QListWidgetItem*);
  void funcListHandle(bool);
  void pictureview(bool);
  void imageSaved(int,const QString&);
  void imageDisplay(QString filename);
  void delete_picture();
  void save_dir_change();
  void timeEvent();
//  void updateRecordTime();
private:
  Qt::WindowFlags winFlags;
  QString fileNameTemp;
  QWidget *ViewWid;
  QWidget *PictureWid;
  QWidget *btnWid;
  QWidget *titleBarWid = nullptr;
//  QWidget *setWid;
  QWidget *rightbtn;
  QWidget *mainWid;

  QHBoxLayout *btnLayout = nullptr;
  QHBoxLayout *mainLayout = nullptr;
  QGridLayout *pictureLayout = nullptr;

  Setting *setWid;
  CameraPage *camerapage;
  TitleBar *pTitleBar = nullptr;
  Button *btnPage = nullptr;
  PictureViewPage *viewpage;

  //保存路径
  QString imagePath;
  QMenu *menu;
  QSettings *setting;

  QTimer *timer;
  //倒计时
  QWidget *dead_time;
  void mousePressEvent(QMouseEvent *event);
  int index = -1;
  int timerId;
  int dead_time_sec;
  int dead_time_sec_tmp=0;
};
#endif // MAINWINDOW_H
