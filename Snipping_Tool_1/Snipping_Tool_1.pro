#-------------------------------------------------
#
# Project created by QtCreator 2016-05-29T17:15:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snipping_Tool_1
TEMPLATE = app

DEFINES+=QT_DISABLE_DEPRECATED_BEFORE=0x000000

SOURCES += main.cpp\
        mainwindow.cpp \
    screenshot.cpp

HEADERS  += mainwindow.h \
    screenshot.h

FORMS    += mainwindow.ui \
    screenshot.ui
