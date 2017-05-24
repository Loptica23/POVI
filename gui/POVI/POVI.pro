#-------------------------------------------------
#
# Project created by QtCreator 2017-01-29T13:22:55
#
#-------------------------------------------------

QT      += core gui
QT      += sql

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


SOURCES +=  main.cpp\
            mainwindow.cpp\
    logintab.cpp \
    waiting.cpp \
    adminview.cpp \
    empoyersview.cpp \
    dialogforcreatingnewemployee.cpp \
    customersview.cpp \
    customersdialog.cpp \
    ordersview.cpp \
    orderdialog.cpp \
    commandsview.cpp \
    commanddialog.cpp \
    commanddialogkomercialist.cpp \
    commandsviewwaitingontask.cpp \
    commanddialogdesigner.cpp \
    commanddialogstorekeeper.cpp \
    tabview.cpp \
    machinesview.cpp \
    machinedialog.cpp \
    commandsviewisinstate.cpp \
    commanddialogchieofproduction.cpp \
    changepassworddialog.cpp \
    shiftmanagerview.cpp \
    tasksinproductionview.cpp \
    workerview.cpp

HEADERS +=  mainwindow.h\
    logintab.h \
    waiting.h \
    adminview.h \
    empoyersview.h \
    dialogforcreatingnewemployee.h \
    customersview.h \
    customersdialog.h \
    ordersview.h \
    orderdialog.h \
    commandsview.h \
    commanddialog.h \
    commanddialogkomercialist.h \
    commandsviewwaitingontask.h \
    commanddialogdesigner.h \
    commanddialogstorekeeper.h \
    tabview.h \
    machinesview.h \
    machinedialog.h \
    commandsviewisinstate.h \
    commanddialogchieofproduction.h \
    changepassworddialog.h \
    shiftmanagerview.h \
    tasksinproductionview.h \
    workerview.h

FORMS   +=  mainwindow.ui \
    logintab.ui \
    waiting.ui \
    adminview.ui \
    empoyersview.ui \
    dialogforcreatingnewemployee.ui \
    customersview.ui \
    customersdialog.ui \
    ordersview.ui \
    orderdialog.ui \
    commandsview.ui \
    commanddialog.ui \
    commandsviewwaitingontask.ui \
    tabview.ui \
    machinesview.ui \
    machinedialog.ui \
    commandsviewisinstate.ui \
    changepassworddialog.ui \
    shiftmanagerview.ui \
    tasksinproductionview.ui \
    workerview.ui

RESOURCES += resource.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DBConnection/release/ -lDBConnection
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DBConnection/debug/ -lDBConnection
else:unix: LIBS += -L$$OUT_PWD/../DBConnection/ -lDBConnection

INCLUDEPATH += $$PWD/../DBConnection
DEPENDPATH += $$PWD/../DBConnection

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TimeSimulator/release/ -lTimeSimulator
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TimeSimulator/debug/ -lTimeSimulator
else:unix: LIBS += -L$$OUT_PWD/../TimeSimulator/ -lTimeSimulator

INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/../TimeSimulator
