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
#include <QProcess>
#include "camerapage.h"
#include "switchbutton.h"

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

    QPushButton *set;
    QPushButton *theme;
    QPushButton *help;
    QPushButton *about;
    SwitchButton *delaybtn;
    SwitchButton *mirrorbtn;

    QHBoxLayout *delayLayout;
    QHBoxLayout *mirrorLayout;
    QHBoxLayout *settingLayout;
    QHBoxLayout *themeLayout;
    QHBoxLayout *helpLayout;
    QHBoxLayout *aboutLayout;
    QVBoxLayout *vlayout;

    //当前路径
    void init_ui();
signals:

public slots:

private:

};

#endif // SETTING_H
