QT += core
QT += gui

TARGET = lab1CV
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = app

SOURCES += main.cpp \
    cvimage.cpp \
    mykernel.cpp \
    pyramid.cpp \
    octave.cpp

HEADERS += \
    cvimage.h \
    mykernel.h \
    pyramid.h \
    octave.h

