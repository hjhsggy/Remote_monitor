#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T13:51:09
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataMonitorClient
TEMPLATE = app

DESTDIR = ../bin

RC_ICONS = Images\App.ico  #程序图标

SOURCES += main.cpp\
        dialog.cpp \
    drawwnd.cpp \
    textwnd.cpp \
    tempwnd.cpp \
    abpwnd.cpp \
    infownd.cpp \
    strip.cpp \
    stripwnd.cpp \
    thresholddialog.cpp

HEADERS  += dialog.h \
    drawwnd.h \
    textwnd.h \
    tempwnd.h \
    abpwnd.h \
    infownd.h \
    usertype.h \
    strip.h \
    stripwnd.h \
    thresholddialog.h

FORMS    += dialog.ui \
    thresholddialog.ui

RESOURCES += \
    images.qrc
