#include "mainwindow.h"
#include "titlebar.h"
#include <QApplication>
#include <QMainWindow>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  qDebug()<<w.mapToGlobal(QPoint(0,0));
//  w.setGeometry(QRect(500,200,900, 628));
  return a.exec();
}
