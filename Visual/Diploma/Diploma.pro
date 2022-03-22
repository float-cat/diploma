#-------------------------------------------------
#
# Project created by QtCreator 2012-04-23T20:34:08
#
#-------------------------------------------------

QT       += core gui

TARGET = Diploma
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp\
        mainwindow.cpp \
    dialogreg.cpp \
    dialoglogenter.cpp \
    dialogjoin.cpp \
    dialoggame.cpp \
    dialogcreategame.cpp \
    dialogaddparam.cpp \
    dialogclaim.cpp \
    QCards/qcards.cpp

HEADERS  += mainwindow.h \
    dialogreg.h \
    dialoglogenter.h \
    dialogjoin.h \
    dialoggame.h \
    dialogcreategame.h \
    dialogaddparam.h \
    dialogclaim.h \
    QCards/qcards.hpp

FORMS    += mainwindow.ui \
    dialogreg.ui \
    dialoglogenter.ui \
    dialogjoin.ui \
    dialoggame.ui \
    dialogcreategame.ui \
    dialogaddparam.ui \
    dialogclaim.ui
