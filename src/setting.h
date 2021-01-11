#ifndef SETTING_H
#define SETTING_H
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QString>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QAction>
#include <QFileDialog>
#include <QSettings>
#include <QComboBox>
#include <QString>
#include <QMap>
#include <QSettings>
#include <QMenu>
#include <QProcess>
#include "camerapage.h"
#include "switchbutton.h"

#include "daemonipcdbus.h"
class Setting: public QWidget
{
    Q_OBJECT

public:
    Setting(QWidget *parent = 0);
    //  ~Setting();
    QWidget *delay;
    QWidget *mirror;

    QLabel *mirrorlab;
    QLabel *delaylab;
    QLabel *setlab;
    QLabel *themelab;
    QLabel *helplab;
    QLabel *aboutlab;
    QLabel *quitlab;

    QPushButton *set;
    QPushButton *theme;
    QPushButton *help;
    QPushButton *about;
    SwitchButton *delaybtn;
    SwitchButton *mirrorbtn;
    QPushButton *quit;
    QMenu *themeMenu; //设置主题菜单

    QHBoxLayout *delayLayout;
    QHBoxLayout *mirrorLayout;
    QHBoxLayout *settingLayout;
    QHBoxLayout *themeLayout;
    QHBoxLayout *helpLayout;
    QHBoxLayout *aboutLayout;
    QHBoxLayout *quitLayout;
    QVBoxLayout *vlayout;

    DaemonIpcDbus *m_pDaemonIpcDbus;
    void init_ui();
signals:

public slots:

private:
    void initAboutText();
};

#endif // SETTING_H
