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
#include <QListWidget>
#include <QStackedWidget>
#include "titlebar.h"
#include "widgetstyle.h"
#include "button.h"
#include "camerapage.h"
#include "pictureviewpage.h"
#include "setting.h"

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
private slots:
  void funcListHandle(bool);
  void pictureview(bool);
  void imageSaved(int,const QString&);
  void imageDisplay(int,QImage);
//  void updateRecordTime();
private:
  Qt::WindowFlags winFlags;

  QWidget *ViewWid;
  QWidget *PictureWid;
  QWidget *btnWid;
  QWidget *titleBarWid = nullptr;
  QWidget *setWid;
  QWidget *rightbtn;
  QWidget *mainWid;

  QHBoxLayout *btnLayout = nullptr;
  QHBoxLayout *mainLayout = nullptr;
  QGridLayout *pictureLayout = nullptr;

  Setting *set;
  CameraPage *camerapage;
  TitleBar *pTitleBar = nullptr;
  Button *btnPage = nullptr;
  PictureViewPage *viewpage;



};
#endif // MAINWINDOW_H
