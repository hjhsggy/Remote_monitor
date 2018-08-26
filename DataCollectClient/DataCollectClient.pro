#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T15:25:55
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataCollectClient
TEMPLATE = app

DESTDIR = ../bin

RC_ICONS = Images\DataCollectClient.ico  #程序图标

SOURCES += main.cpp\
        dialog.cpp \
    drawwnd.cpp \
    textwnd.cpp \
    strip.cpp \
    stripwnd.cpp \
    tempwnd.cpp \
    abpwnd.cpp

HEADERS  += dialog.h \
    drawwnd.h \
    textwnd.h \
    strip.h \
    stripwnd.h \
    tempwnd.h \
    abpwnd.h

FORMS    += dialog.ui
