#include "mainwindow.h"
#include "titlebar.h"
#include <QApplication>
#include <QMainWindow>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  w.setGeometry(QRect(500,200,900, 628));
  return a.exec();
}
