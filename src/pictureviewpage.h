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
#include <QListView>
#include "camerapage.h"

class PictureViewPage:public QWidget
{
    Q_OBJECT
//  Q_DECLARE_METATYPE(ItemData)
public:

  PictureViewPage();
  QPixmap *map;
  QListWidget *listWidget;
  QListView *listview;
  QPushButton *deleteBtn;
  void createListWidget(QString &);
  void initListWidget();
  void initListView();


public slots:
//  void  itemclicked(QListWidgetItem*);
private:

  QLabel *text;
  QWheelEvent *wheel;
  QListWidgetItem *item;
  QHBoxLayout *hlayout;
  QWidget *btnpage;
  QVBoxLayout *vlayout;
  QGridLayout *grid;
  QHBoxLayout *btnlayout;
  QLabel *imageLabel;
  QStackedLayout *stackWidgetLayout = nullptr;
};

#endif // PICTUREVIEWPAGE_H
