#-------------------------------------------------
#
# Project created by QtCreator 2015-12-02T12:54:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Network-Connectivity
TEMPLATE = app


SOURCES += frontend/main.cpp\
		frontend/mainwindow.cpp \
    backend/Connectivity.cpp \
    backend/Graph.cpp \
    backend/Link.cpp \
    backend/NetworkIdGenerator.cpp \
    backend/Path.cpp \
    backend/ResidualGraph.cpp

HEADERS  += frontend/mainwindow.h \
    backend/Connectivity.h \
    backend/Graph.h \
    backend/Link.h \
    backend/NetworkIdGenerator.h \
    backend/Node.h \
    backend/Path.h \
    backend/ResidualGraph.h \
    backend/Subnode.h

FORMS    += frontend/mainwindow.ui
