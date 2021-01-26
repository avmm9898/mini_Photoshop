#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T14:42:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Photoshop_opencv
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH +=C:\opencv\build\include

        C:\opencv\build\include\opencv

        C:\opencv\build\include\opencv2

CONFIG(debug,debug|release)
{
    LIBS += C:\opencv\build\x64\vc14\lib\opencv_world331d.lib

}
CONFIG(release,debug|release)
{
    LIBS += C:\opencv\build\x64\vc14\lib\opencv_world331.lib
}

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        photo_frame.cpp

HEADERS += \
        mainwindow.h \
        photo_frame.h

FORMS += \
        mainwindow.ui \
        photo_frame.ui
