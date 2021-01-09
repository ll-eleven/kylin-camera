#include "mainwindow.h"
#include "titlebar.h"
#include <QApplication>
#include <QMainWindow>
#include <QTranslator>
#include <QCoreApplication>
#include <QPixmap>
#include <QDebug>
#include <QLibraryInfo>
#include <unistd.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/file.h>
#include <fcntl.h>
#include <syslog.h>
#include "xatom-helper.h"
#define TRANS_PATH  "/opt/kylin-camera/translations/"

int main(int argc, char *argv[])
{
    //互斥锁，防止打开多个程序
//    int fd = open(TRANS_PATH,O_RDONLY);
//    flock(fd,LOCK_UN);
//    if(fd == -1) return -1;
//    int ret = flock(fd,LOCK_EX | LOCK_NB);
//    if(ret == -1) return -1;

    //设配4k屏
#if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))

  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

#endif

#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))

  QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

#endif
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
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator();
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    {
        a.installTranslator(translator);
    }
    else
    {
        qDebug() << "加载中文失败";
    }


    MainWindow w;
#ifndef __V10__
    //添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(w.winId(), hints);
#endif
    w.show();
    return a.exec();
}
