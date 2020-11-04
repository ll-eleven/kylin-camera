#ifndef PICTUREVIEWPAGE_H
#define PICTUREVIEWPAGE_H
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QListWidget>
#include <QDir>
#include <QStackedLayout>
#include <QScrollBar>
#include <QWheelEvent>
#include <QVBoxLayout>
#include "camerapage.h"

class PictureViewPage:public QWidget
{
public:
  PictureViewPage();
  QPixmap *map;
  QListWidget *listWidget;
  void createListWidget(QString &);
  void initListWidget();

private:
  QLabel *text;
  QWheelEvent *wheel;
  QListWidgetItem *item;
  QHBoxLayout *hlayout;
  QVBoxLayout *vlayout;
  QGridLayout *grid;

  QLabel *imageLabel;
  QStackedLayout *stackWidgetLayout = nullptr;
};

#endif // PICTUREVIEWPAGE_H
