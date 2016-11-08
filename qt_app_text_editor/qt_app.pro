#-------------------------------------------------
#
# Project created by QtCreator 2016-11-08T14:08:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_app
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    widget.cpp \
    eventdialog.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    widget.h \
    eventdialog.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    widget.ui \
    eventdialog.ui

RESOURCES += \
    myresources.qrc
