#-------------------------------------------------
#
# Project created by QtCreator 2015-01-06T17:16:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Life
TEMPLATE = app


SOURCES += main.cpp\
        lifewindow.cpp \
    grid.cpp \
    LifeEngine/life.cpp

HEADERS  += lifewindow.h \
    grid.h \
    LifeEngine/life.h

RESOURCES +=
