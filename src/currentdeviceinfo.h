#ifndef CURRENTDEVICEINFO_H
#define CURRENTDEVICEINFO_H
#include <QPair>
#include <QList>
class CurrentDeviceInfo
{
public:
    CurrentDeviceInfo();
    static QList<QPair<uint,uint>> available_size;
    static uint available_format;
    static QPair<uint,uint> current_size;
};

#endif // CURRENTDEVICEINFO_H
