#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T22:43:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = AnalyseNumerique
TEMPLATE = app


SOURCES += main.cpp principal.cpp qcustomplot.cpp \
    traitement.cpp

HEADERS  += principal.h qcustomplot.h \
    traitement.h

FORMS    += principal.ui
