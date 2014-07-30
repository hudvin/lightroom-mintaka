#-------------------------------------------------
#
# Project created by QtCreator 2014-07-11T19:30:14
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mintaka
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    keywordsloader.cpp \
    dbwrapper.cpp \
    csvreader.cpp \
    pathutils.cpp \
    dndtableview.cpp \
    imagelistwidget.cpp

HEADERS  += mainwindow.h \
    keywordsloader.h \
    dbwrapper.h \
    csvreader.h \
    pathutils.h \
    structures.h \
    dndtableview.h \
    imagelistwidget.h \
    constants.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
