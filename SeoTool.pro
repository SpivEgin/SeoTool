#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T23:26:46
#
#-------------------------------------------------

QT       += core gui webkitwidgets sql
#QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeoTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CommandAbstract.cpp \
    OpenGoogle.cpp \
    SearchSiteCmd.cpp \
    DatabaseConnector.cpp \
    KeywordObject.cpp \
    DomainObject.cpp

HEADERS  += mainwindow.h \
    CommandAbstract.h \
    OpenGoogle.h \
    SearchSiteCmd.h \
    DatabaseConnector.h \
    KeywordObject.h \
    DomainObject.h

FORMS    += mainwindow.ui
