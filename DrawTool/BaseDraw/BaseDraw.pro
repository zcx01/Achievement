#-------------------------------------------------
#
# Project created by QtCreator 2019-07-06T16:21:57
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BaseTool
TEMPLATE = lib
DEFINES += QT_DEPRECATED_WARNINGS CDRAW_LIBRARY
libs+= ZXml HfFrameReflect
include(../../../../../hfsrc/HfPri/hfpath.pri)
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    CGraphicsView.cpp \
    CZBaseTool.cpp \
    CZBase.cpp \
    CManagementItem.cpp \
    CManagementTool.cpp \
    CZStaticFun.cpp \
    DataTransmit.cpp \
    ComputeGeometry.cpp \
    CZDrawManagement.cpp

HEADERS += \
    CGraphicsView.h \
    cdraw_global.h \
    CZBaseTool.h \
    CZBase.h \
    czdrawstruct.h \
    CManagementItem.h \
    CManagementTool.h \
    CZStaticFun.h \
    DataTransmit.h \
    ComputeGeometry.h \
    CZDrawManagement.h
