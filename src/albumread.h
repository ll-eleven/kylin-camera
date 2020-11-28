#ifndef ALBUMREAD_H
#define ALBUMREAD_H

#include <QThread>
#include <QFileInfo>
class AlbumRead : public QThread
{
    Q_OBJECT
public:
    explicit AlbumRead(QString str);

private:
    void run();
    QString filename;

signals:
    void finish(QString str);
};

#endif // ALBUMREAD_H
