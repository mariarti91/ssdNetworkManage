QT += core network sql
QT -= gui

TEMPLATE = app

DESTDIR = ../bin

TARGET = ssd.bin

SOURCES += ../src/main.cpp \
           ../src/MyServer.cpp \
           ../src/MyNetworkManager.cpp \
           ../src/MySocket.cpp \
           ../src/MyDataBase.cpp

HEADERS += ../src/MyServer.h \
           ../src/MyNetworkManager.h \
           ../src/MySocket.h \
           ../src/MyDataBase.h


LIBS += -L ../../../qamqp/ -l qamqp

INCLUDEPATH += ../../../qamqp
