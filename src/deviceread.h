#ifndef DEVICEREAD_H
#define DEVICEREAD_H
#include <QThread>
#include <QTimer>
#include "setting.h"
#include "camerapage.h"

class DeviceRead : public QThread
{
    Q_OBJECT
public:
    explicit DeviceRead();
public slots:
    void run();

signals:
    void finish();
};

#endif // DEVICEREAD_H
