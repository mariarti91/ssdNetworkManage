QT += core network
QT -= gui

TEMPLATE = app

DESTDIR = ../bin

TARGET = ssd.bin

SOURCES += ../src/main.cpp \
           ../src/MyServer.cpp \
           ../src/MyNetworkManager.cpp \
           ../src/MySocket.cpp

HEADERS += ../src/MyServer.h \
           ../src/MyNetworkManager.h \
           ../src/MySocket.h


LIBS += -L ../../../qamqp/ -l qamqp

INCLUDEPATH += ../../../qamqp
