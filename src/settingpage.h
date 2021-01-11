#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H
#include <QWidget>
#include "setting.h"
class SettingPage:public QWidget
{
        Q_OBJECT
public:
    SettingPage(QPoint *p):pos(p){}
    SettingPage();

    QString current_dir;
    QLabel *current_dir_lab;
    QLabel *current_cameraDev;
    QLabel *current_vedioDev;
    void init_ui();
    void Geometry(QPoint *);

signals:
    void dir_change();
    void change_dev(const char *);
    void change_resolutions(QPair<uint,uint>);
  //  void scale_change();

public slots:
    void dir_click();
    void change_item();
    void change_cameraDevice(const char *);
    void close();
    void confirm_click();
    void cancel_click();
    void update();
  //  void scale_click();
  //  void cameraDevice_click();
  //  void vedioDevice_click();
  //  void delay_click();
  //  void mirror_click();

protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    QLabel *dirlab;
    QLabel *scalelab;
    QLabel *cameraDevicelab;
    QLabel *vedioDevicelab;

    //功能按钮部分
    QPushButton *dir;
    QComboBox *scale;
    QComboBox *cameraDevice;
    QComboBox *vedioDevice;
    SwitchButton *delaybtn;
    SwitchButton *mirrorbtn;
    QPushButton *confirm;
    QPushButton *cancel;

    QVBoxLayout *vlayout;
    //当前路径
    QHBoxLayout *btnLayout;
    QHBoxLayout *dirLayout;
    QHBoxLayout *scaleLayout;
    QHBoxLayout *cameraDeviceLayout;
    QHBoxLayout *vedioDeviceLayout;
    QPoint *pos;
    QPoint m_start;
    QMap<QString,QString> camera_name2dev;
    QMap<QString,QString> audio_name2dev;
    QString scale_str;
    QSettings *theme_setting = new QSettings;
    static int dev_change;
    static bool press;
};

#endif // SETTINGPAGE_H
