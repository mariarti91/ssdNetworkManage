QT += core network sql
QT -= gui

TEMPLATE = app

TARGET = ssd.bin

DESTDIR = ../bin

SOURCES = ../src/main.cpp \
    ../src/MySocket.cpp \
    ../src/MyNetworkManager.cpp

HEADERS += \
    ../src/MySocket.h \
    ../src/MyNetworkManager.h