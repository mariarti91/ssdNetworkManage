QT += core network
QT -= gui

TEMPLATE = app

DESTDIR = ../bin

TARGET = ssd.bin

SOURCES += ../src/main.cpp \
           ../src/MyServer.cpp

HEADERS += ../src/MyServer.h

LIBS += -L ../../../qamqp/ -l qamqp

INCLUDEPATH += ../../../qamqp
