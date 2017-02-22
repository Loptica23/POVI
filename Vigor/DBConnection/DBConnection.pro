#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T21:36:16
#
#-------------------------------------------------

QT       -= gui
QT       += sql

TARGET = DBConnection
TEMPLATE = lib

DEFINES += DBCONNECTION_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += dbconnection.cpp \
    dbconnectionimpl.cpp \
    employee.cpp \
    customer.cpp \
    order.cpp \
    command.cpp \
    task.cpp \
    tasktypes.cpp

HEADERS += dbconnection.h\
        dbconnection_global.h \
    dbconnectionimpl.h \
    customer.h \
    order.h \
    command.h \
    task.h \
    tasktypes.h

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
