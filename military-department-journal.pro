#-------------------------------------------------
#
# Project created by QtCreator 2013-06-25T12:21:28
#
#-------------------------------------------------

QT       += core gui sql network

QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++
LIBS += -stdlib=libc++
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = military-department-journal
TEMPLATE = app

LIBS += -lz

SOURCES += main.cpp \
    mainwindow.cpp \
    database.cpp \
    documentgenerator.cpp

HEADERS  += mainwindow.h \
    database.h \
    documentgenerator.h

HEADERS += \
    models/universitygroupmodel.h \
    models/teachermodel.h \
    models/troopmodel.h \
    models/militaryprofessionmodel.h \
    models/studentmodel.h \
    models/subjectmodel.h \
    models/evaluationmodel.h \
    models/subjectdurationmodel.h \
    models/universityfacultymodel.h

SOURCES += \
    models/universitygroupmodel.cpp \
    models/teachermodel.cpp \
    models/troopmodel.cpp \
    models/militaryprofessionmodel.cpp \
    models/studentmodel.cpp \
    models/subjectmodel.cpp \
    models/evaluationmodel.cpp \
    models/universityfacultymodel.cpp \
    models/subjectdurationmodel.cpp

HEADERS += \
    widgets/universityfacultywidget.h \
    widgets/basewidget.h \
    widgets/universitygroupwidget.h \
    widgets/teacherwidget.h \
    widgets/troopwidget.h \
    widgets/militaryprofessionwidget.h \
    widgets/studentwidget.h \
    widgets/subjectwidget.h \
    widgets/evaluationwidget.h \
    widgets/subjectdurationwidget.h

SOURCES += \
    widgets/universityfacultywidget.cpp \
    widgets/basewidget.cpp \
    widgets/troopwidget.cpp \
    widgets/universitygroupwidget.cpp \
    widgets/teacherwidget.cpp \
    widgets/militaryprofessionwidget.cpp \
    widgets/studentwidget.cpp \
    widgets/subjectwidget.cpp \
    widgets/evaluationwidget.cpp \
    widgets/subjectdurationwidget.cpp

FORMS    += mainwindow.ui

TRANSLATIONS += linguas_ru.ts

OTHER_FILES = \
    README.md \
    LICENSE.md

include(qt4table-steroids/qt4table-steroids.pri)
include(docx-replacer/docx-replacer.pri)

RESOURCES += \
    resources.qrc
