#-------------------------------------------------
#
# Project created by QtCreator 2019-08-05T21:33:14
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ItemDraw
TEMPLATE = lib

libs+= BaseTool DrawToolPublic HfFrameReflect
include(../../../../../hfsrc/HfPri/hfpath.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


contains(QT,svg){
DEFINES+= SVGEXIST
}

SOURCES += \
    DrawRect.cpp \
    CDrawImage.cpp \
    CDrawLine.cpp \
    CRotaryImage.cpp \
    CDrawGraphicsRect.cpp \
    DrawEllipse.cpp \
    DrawDiamond.cpp \
    DrawSvg.cpp \
    FoldLine.cpp \
    AssistLine.cpp \
    TimeScale.cpp \
    FlowTextGrid.cpp \
    DisPlayRange.cpp \
    DSector.cpp \
    GraduationRuler/BaseRule.cpp

HEADERS += \
    DrawRect.h \
    CDrawImage.h \
    CDrawLine.h \
    CRotaryImage.h \
    CDrawGraphicsRect.h \
    DrawEllipse.h \
    DrawDiamond.h \
    DrawSvg.h \
    FoldLine.h \
    AssistLine.h \
    TimeScale.h \
    FlowTextGrid.h \
    DisPlayRange.h \
    DSector.h \
    GraduationRuler/BaseRule.h
