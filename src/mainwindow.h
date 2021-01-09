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
#include "deviceread.h"
#include <QDateTime>
#include <QStandardPaths>
//#include <QGSettings/QGSettings>
#include <QPixmap>
#include "albumread.h"
#include "settingpage.h"
#include "aboutwidget.h"
#include <QProcess>
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //设置通用UI
    void setCommonUI();
    //应用置顶
    void stayTop();

    void paintEvent(QPaintEvent *event);
    //点击设置按钮
    void funcListItemClicked(QListWidgetItem* item);

    void setbutton();
    void setcamerapage();
    void setpicturepage();


    //声明配置文件
    QSettings *picture_setting = new QSettings;
    QSettings *setting = new QSettings;
    QPoint temp;
    bool settingShow = false;
    static int picture_number;
signals:
    void click_vedio();
    void click_picture();
private slots:
    void takePhoto(QString name, bool isvideo);
    QString creatName();
    QString trueName(QString name);
    void startCommend(QString cmd);

    void clickPause();
    //  void clickRestore();
    void clickPhoto();
    void clickStartRecord();
    void clickStopRecord();
    void clickBrust();
    void itemclicked(QListWidgetItem*);
    void itemDoubleClicked(QListWidgetItem*);
    void funcListHandle(bool);
    void pictureview(bool);
    void imageSaved(int,const QString&);
    void imageDisplay(QString filename);
    void delete_picture();
    void save_dir_change();
    void timeEvent();
    void setMaxWindow(bool);
    void settingPageShow();
    void updateRecordTime();
    void imageView(QString);
    void quit();
    void initAbout();
    void initHelp();
    void thememenu();
protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
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

    DeviceRead *devRead;
    //各个组件
    Setting *setWid = nullptr;
    CameraPage *camerapage;
    TitleBar *pTitleBar = nullptr;
    Button *btnPage = nullptr;
    PictureViewPage *viewpage;
    SettingPage *setPage;


    QString imagePath; //保存路径

    AboutWidget *aboutWinWidget;

    //监听设备文件
    QFileSystemWatcher *watcher;

    QTimer *timer = nullptr;
    //倒计时
    QWidget *dead_time;

    QProcess *proc;
    QPoint m_start;
    QPoint m_end;
//    void changeEvent(QEvent *);
    void keyPressEvent(QKeyEvent *event);
    int index = -1;
    int timerId;
    int dead_time_sec;
    int dead_time_sec_tmp = 0;
    bool is_vedio = false;
    bool Burst_mode = false;
};
#endif // MAINWINDOW_H
