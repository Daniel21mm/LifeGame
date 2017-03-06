#-------------------------------------------------
#
# Project created by QtCreator 2017-03-04T00:06:08
#
#-------------------------------------------------

QT       += core gui opengl

CONFIG +=c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LifeGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cell.cpp \
    map.cpp \
    paint.cpp

HEADERS  += mainwindow.h \
    cell.h \
    map.h \
    paint.h
