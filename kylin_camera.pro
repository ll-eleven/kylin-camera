QT += core gui
QT += dbus x11extras KWindowSystem
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#CONFIG += no_keywords
CONFIG += c++11
#QMAKE_CXXFLAGS += -g
TEMPLATE = app
TARGET = kylin-camera

LIBS +=-lpthread
LIBS +=-lX11

lessThan(QT_MAJOR_VERSION, 4) | lessThan(QT_MINOR_VERSION, 9) {
    message("QT_VERSION ("$$QT_VERSION")")
    DEFINES += __V10__
    QT      -= x11extras
    QT      -= KWindowSystem
    LIBS    -= -lpthread
    LIBS    -= -lX11
}
icons.path = /usr/share/pixmaps/
target.path = /usr/bin/
#target.path = /opt/kylin-camera/bin/
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

# 适配窗口管理器圆角阴影


INCLUDEPATH += /usr/include/kylincameralibs/

SOURCES += \
    src/about.cpp \
    src/albumread.cpp \
    src/button.cpp \
    src/camerapage.cpp \
    src/currentdeviceinfo.cpp \
    src/deviceread.cpp \
    src/help.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mylistwidgetitem.cpp \
    src/pictureviewpage.cpp \
    src/setting.cpp \
    src/settingpage.cpp \
    src/switchbutton.cpp \
    src/titlebar.cpp \
    src/widgetstyle.cpp \
    src/xatom-helper.cpp

HEADERS += \
    src/about.h \
    src/albumread.h \
    src/button.h \
    src/camerapage.h \
    src/currentdeviceinfo.h \
    src/deviceread.h \
    src/help.h \
    src/mainwindow.h \
    src/mylistwidgetitem.h \
    src/pictureviewpage.h \
    src/setting.h \
    src/settingpage.h \
    src/switchbutton.h \
    src/titlebar.h \
    src/widgetstyle.h \
    src/xatom-helper.h

RESOURCES += \
    image.qrc \

TRANSLATIONS += translations/kylin-camera_zh_CN.ts
TRANSLATIONS += translations/kylin-camera_bo.ts





