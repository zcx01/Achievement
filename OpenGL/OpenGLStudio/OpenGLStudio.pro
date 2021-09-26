#-------------------------------------------------
#
# Project created by QtCreator 2020-08-08T16:53:36
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGLStudio
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        TriangleWidget.cpp \
    openglwindow.cpp \
    MainNavigationWidget.cpp \
    GLSL.cpp \
    Trans.cpp \
    Coordinate.cpp \
    Cude.cpp \
    CameraWidget.cpp \
    Lighting/Colors.cpp \
    Lighting/light2.cpp \
    Lighting/light3.cpp \
    Lighting/light4.cpp \
    ETexture.cpp \
    Base/Buffer.cpp \
    Base/Camera.cpp \
    Base/Shader.cpp \
    Base/VertexArrayObject.cpp \
    Lighting/light5.cpp \
    Lighting/light6.cpp \
    Lighting/light7.cpp \
    Lighting/light8.cpp \
    Base/Mesh.cpp \
    Base/GlModel.cpp \
    AssimpModel/AssimpModel.cpp \
    HighOPenGL/TemplateTest.cpp \
    HighOPenGL/Blending.cpp \
    HighOPenGL/Blending2.cpp \
    HighOPenGL/FaceCulling.cpp \
    Base/FrameBuffer.cpp \
    HighOPenGL/FrameTexture.cpp \
    Base/CTexture2D.cpp \
    HighOPenGL/Skybox.cpp \
    Base/CTextureCude.cpp \
    HighOPenGL/EnvironmentMapping.cpp \
    HighOPenGL/UniformBuffer.cpp \
    HighOPenGL/Geometry.cpp \
    HighOPenGL/Planet.cpp \
    HighOPenGL/Instantiation.cpp \
    HighOPenGL/instantiationarray.cpp \
    HighOPenGL/MSAA.cpp \
    HighLight/BlinnPhong.cpp

HEADERS += \
        TriangleWidget.h \
    openglwindow.h \
    MainNavigationWidget.h \
    GLSL.h \
    Trans.h \
    Coordinate.h \
    Cude.h \
    CameraWidget.h \
    Lighting/Colors.h \
    Lighting/light2.h \
    Lighting/light3.h \
    Lighting/light4.h \
    ETexture.h \
    Base/Buffer.h \
    Base/Camera.h \
    Base/Shader.h \
    Base/VertexArrayObject.h \
    Lighting/light5.h \
    Lighting/light6.h \
    Lighting/light7.h \
    Lighting/light8.h \
    Base/Mesh.h \
    Base/gldefinde.h \
    Base/GlModel.h \
    AssimpModel/AssimpModel.h \
    HighOPenGL/TemplateTest.h \
    HighOPenGL/Blending.h \
    HighOPenGL/Blending2.h \
    HighOPenGL/FaceCulling.h \
    Base/FrameBuffer.h \
    HighOPenGL/FrameTexture.h \
    Base/CTexture2D.h \
    HighOPenGL/Skybox.h \
    Base/CTextureCude.h \
    HighOPenGL/EnvironmentMapping.h \
    HighOPenGL/UniformBuffer.h \
    HighOPenGL/Geometry.h \
    HighOPenGL/Planet.h \
    HighOPenGL/Instantiation.h \
    HighOPenGL/instantiationarray.h \
    HighOPenGL/MSAA.h \
    HighLight/BlinnPhong.h

FORMS += \
    MainNavigationWidget.ui

RESOURCES += \
    glsl.qrc

INCLUDEPATH+=./Base \
            $$PWD/assimp/include \

LIBS+=$$PWD/assimp/lib/libassimp.dll.a \
      $$PWD/assimp/lib/libzlibstatic.a \

#DISTFILES += \
#    config/Textrue/awesomeface.jpg

