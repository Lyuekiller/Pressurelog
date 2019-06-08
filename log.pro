#-------------------------------------------------
#
# Project created by QtCreator 2019-05-26T09:45:33
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = log
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    cevents.cpp \
    qcustomplot.cpp \
    general.cpp \
    imagedisplay.cpp \
    Pressurelog.cpp \
    imagewin.cpp \
    controldialog.cpp

HEADERS += \
        widget.h \
    cevents.h \
    qcustomplot.h \
    general.h \
    imagedisplay.h \
    Pressurelog.h \
    imagewin.h \
    controldialog.h

FORMS += \
        widget.ui \
    imagedisplay.ui \
    imagewin.ui \
    controldialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
