QT += core gui
QT += multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TEMPLATE = app
TARGET = kylin-camera

icons.path = /usr/share/pixmaps/
target.path = /opt/kylin-camera/bin/
target.source += $$TARGET
desktop.path = /usr/share/applications/
desktop.files = kylin-camera.desktop

#material.path = $$[QT_INSTALL_QML]/

qm_files.path = /opt/kylin-camera/translations/
qm_files.files += translations/*.qm
INSTALLS += qm_files \
            target \
            desktop



# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


LIBS += -lkylincamera \
        -lgpac \
        -lx264

INCLUDEPATH += /usr/include/kylincameralibs/

SOURCES += \
    src/albumread.cpp \
    src/button.cpp \
    src/camerapage.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mylistwidgetitem.cpp \
    src/pictureviewpage.cpp \
    src/setting.cpp \
    src/switchbutton.cpp \
    src/titlebar.cpp \
    src/widgetstyle.cpp

HEADERS += \
    src/albumread.h \
    src/button.h \
    src/camerapage.h \
    src/mainwindow.h \
    src/mylistwidgetitem.h \
    src/pictureviewpage.h \
    src/setting.h \
    src/switchbutton.h \
    src/titlebar.h \
    src/widgetstyle.h

RESOURCES += \
    image.qrc \

TRANSLATIONS += translations/kylin-camera_zh_CN.ts
TRANSLATIONS += translations/kylin-camera_bo.ts

#FORMS += \
#    mainwindow.ui

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
