#-------------------------------------------------
#
# Project created by QtCreator 2017-01-29T13:22:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = POVI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=  gui/sources/main.cpp\
            gui/sources/mainwindow.cpp\
            databaseconnection/sources/databaseconnection.cpp

HEADERS +=  gui/headers/mainwindow.h\
            databaseconnection/headers/databaseconnection.h

FORMS   +=  gui/forms/mainwindow.ui

INCLUDEPATH +=  gui/headers\
                databaseconnection/headers
