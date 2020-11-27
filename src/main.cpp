#include "mainwindow.h"
#include "titlebar.h"
#include <QApplication>
#include <QMainWindow>
#include <QTranslator>
#include <QCoreApplication>
#include <QPixmap>
#include <QDebug>
#define TRANS_PATH "/opt/kylin-camera/translations/"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString trans_path;
    if (QDir(TRANS_PATH).exists()) {
        trans_path = TRANS_PATH;
    }
    else {
        trans_path = qApp->applicationDirPath() + "/translations";
    }
    QTranslator app_trans;
    QString locale = QLocale::system().name();
    if (locale == "zh_CN") {
        if(app_trans.load("kylin-camera_" + locale + ".qm", trans_path))
           qDebug()<<"加载翻译文件："<< a.installTranslator(&app_trans);
    }

    MainWindow w;
    w.show();

  return a.exec();
}
