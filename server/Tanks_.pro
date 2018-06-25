#-------------------------------------------------
#
# Project created by QtCreator 2018-06-14T17:36:05
#
#-------------------------------------------------

QT       += core gui
QT += gamepad

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tanks_
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    track.cpp \
    tank.cpp \
    turret.cpp \
    gun.cpp \
    vision.cpp \
    body.cpp \
    action.cpp \
    player.cpp \
    gamepadmngr.cpp

HEADERS += \
        mainwindow.h \
    track.h \
    tank.h \
    turret.h \
    gun.h \
    vision.h \
    body.h \
    action.h \
    player.h \
    gamepadmngr.h

FORMS += \
        mainwindow.ui