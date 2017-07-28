#-------------------------------------------------
#
# Project created by QtCreator 2016-05-31T20:00:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ultimate_Cut_out
TEMPLATE = app

DEFINES+=QT_DISABLE_DEPRECATED_BEFORE=0x000000

SOURCES += main.cpp\
        mainwindow.cpp \
    screenshot.cpp \
    sizegripitem.cpp

HEADERS  += mainwindow.h \
    screenshot.h \
    sizegripitem.h

FORMS    += mainwindow.ui \
    screenshot.ui
