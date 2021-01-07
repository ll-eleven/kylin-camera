#include "albumread.h"
#include <QDebug>
AlbumRead::AlbumRead(QString str)
{
    filename = str;
    connect(this,SIGNAL(finished()),this,SLOT(deleteLater()));
}


void AlbumRead::run()
{
    QFileInfo dir(filename);
    QFile file(filename);
    for(int i = 0;i < 50; i++)
    {
        if (dir.exists())
        {
            if(file.open(QIODevice::ReadOnly))
            {
                file.close();
                emit finish(filename);
                return;
            }
        }
        QThread::msleep(100);
    }
}
