QT += core network
QT -= gui

TEMPLATE = app

TARGET = uspd.bin

DESTDIR = ../bin

SOURCES = ../src/main.cpp \
    ../src/MyServer.cpp \
   # ../../SSD/src/MySocket.cpp

HEADERS += \
    ../src/MyServer.h \
   # ../../SSD/src/MySocket.h
    ../src/comands.h
