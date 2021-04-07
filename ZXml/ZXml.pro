#-------------------------------------------------
#
# Project created by QtCreator 2018-07-20T12:34:49
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZXml
TEMPLATE = lib

include(../../../../hfsrc/HfPri/hfpath.pri)

DEFINES+=ZXML_LIBRARY

SOURCES += \
    CXml.cpp

HEADERS  += \
    zxml_global.h \
    CXml.h
