#-------------------------------------------------
#
# Project created by QtCreator 2017-04-15T01:59:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NuCapManager
TEMPLATE = app

LIBS += -L .\libs -lWS2_32

#INCLUDEPATH += utils/
INCLUDEPATH += qttelnet/
INCLUDEPATH += ui/

SOURCES += main.cpp \
    qttelnet/qttelnet.cpp \
    ui/mainwindow.cpp

HEADERS  += qttelnet/qttelnet.h \
    ui/mainwindow.h \
    utils/Log.h \
    datatype.h

FORMS    += ui/mainwindow.ui
