QT += core
QT -= gui

TARGET = qiniu
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -L. -lqiniu -lcurllib -llibeay32 -lssleay32 -lopenldap

SOURCES += main.cpp

#HEADERS +=

#DISTFILES +=

