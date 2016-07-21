#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T17:55:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebChannelTest
TEMPLATE = app

QT += websockets webengine webenginewidgets

SOURCES += main.cpp\
        mainwindow.cpp \
    concreteprotocol.cpp \
    exportedobject.cpp

HEADERS  += mainwindow.h \
    concreteprotocol.h \
    exportedobject.h

DEFINES += "BUILD_DIR=\"\\\""$$OUT_PWD"\\\"\""

# Ensure HTML is available for application

html.files = index.html
html.files += title.png
html.files += inject.js
html.path = $$OUT_PWD
COPIES += html
