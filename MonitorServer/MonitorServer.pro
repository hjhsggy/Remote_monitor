#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T20:33:41
#
#-------------------------------------------------

QT       += core gui network
QT       += sql #数据库支持

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonitorServer
TEMPLATE = app

DESTDIR = ../bin

RC_ICONS = Images\Server.ico  #程序图标


SOURCES += main.cpp\
        dialog.cpp \
    clientsocket.cpp \
    listensocket.cpp

HEADERS  += dialog.h \
    clientsocket.h \
    listensocket.h

FORMS    += dialog.ui
