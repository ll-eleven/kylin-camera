#include "deviceread.h"

DeviceRead::DeviceRead()
{
//    connect(this,SIGNAL(finished()),this,SLOT(deleteLater()));
}

//等待完成设备文件的读取,更新设备列表
void DeviceRead::run(){
    //简单暂停一秒

//    if(access(current_indevice,F_OK) == 0 && has_device == 0)
//    {
//        int i = 0;
//        while(1)
//        {
//         sleep(1);
//         memset(&s_stat , 0x00 , sizeof(struct stat));
//         int ret = stat(current_indevice , &s_stat);
//         qDebug() <<"camerapage.cpp:271";
//        //
//         if(ret == -1)
//         {
//             return;
//         }
//         if((s_stat.st_mode == (unsigned long)8624))
//         {
//             qDebug()<<"camerapage.cpp:279";
//             creatCameraPage(current_indevice);
//             return ;
//         }
//        }
//    }
    qDebug() << "deviceread.cpp:34";
    QThread::msleep(1000);
    *CameraPage::cameras = QCameraInfo::availableCameras();

    emit finish();

}

