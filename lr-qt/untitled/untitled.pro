#-------------------------------------------------
#
# Project created by QtCreator 2014-07-11T19:30:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    keywordsloader.cpp

HEADERS  += mainwindow.h \
    keywordsloader.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
