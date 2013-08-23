#-------------------------------------------------
#
# Project created by QtCreator 2013-06-25T12:21:28
#
#-------------------------------------------------

QT       += core gui sql

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = military-department-journal
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    database.cpp \
    universitygroupwidget.cpp \
    universitygroupmodel.cpp \
    teachermodel.cpp \
    basewidget.cpp \
    teacherwidget.cpp \
    troopwidget.cpp \
    troopmodel.cpp \
    militaryprofessionmodel.cpp \
    militaryprofessionwidget.cpp \
    studentwidget.cpp \
    studentmodel.cpp

HEADERS  += mainwindow.h \
    database.h \
    universitygroupwidget.h \
    universitygroupmodel.h \
    teachermodel.h \
    basewidget.h \
    teacherwidget.h \
    troopwidget.h \
    troopmodel.h \
    militaryprofessionmodel.h \
    militaryprofessionwidget.h \
    studentwidget.h \
    studentmodel.h

FORMS    += mainwindow.ui \
    studentswidget.ui

TRANSLATIONS += linguas_ru.ts

OTHER_FILES = \
    README.md \
    LICENSE.md

include(qt4table-steroids/qt4table-steroids.pri)

RESOURCES += \
    resources.qrc
