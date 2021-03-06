QT += core network sql
QT -= gui

TEMPLATE = app

TARGET = ssd.bin

DESTDIR = ../bin

SOURCES = ../src/main.cpp \
    ../src/MySocket.cpp \
    ../src/MyNetworkManager.cpp \
    ../src/MyDataManager.cpp \
    ../src/MyDataBase.cpp \
    ../src/MyServer.cpp

HEADERS += \
    ../src/MySocket.h \
    ../src/MyNetworkManager.h \
    ../src/MyDataManager.h \
    ../src/MyDataBase.h \
    ../src/MyServer.h
