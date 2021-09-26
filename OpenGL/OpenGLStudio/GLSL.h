#ifndef GLSL_H
#define GLSL_H

#include <QWidget>
#include "openglwindow.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLShader>

class GLSL : public OpenGLWindow
{
public:
    GLSL();
    ~GLSL();


protected:
    // QWindow interface
protected:
    void resizeEvent(QResizeEvent *);
private:
    void initialize() override;
    void render() override;

    //绘制三角形
    void drawTriangle();

    //绘制矩形
    void drawRect();

private:
    GLuint vertexShader;    //顶点着色器
    GLuint shaderProgram;   //片段着色器



};
#endif // GLSL_H
