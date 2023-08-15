#ifndef GLYUVWIDGET_H
#define GLYUVWIDGET_H
/*

参考链接：
https://blog.csdn.net/weixin_42887343/article/details/112545633?spm=1001.2101.3001.6650.11&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-11-112545633-blog-123295253.pc_relevant_3mothn_strategy_recovery&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-11-112545633-blog-123295253.pc_relevant_3mothn_strategy_recovery&utm_relevant_index=12

https://blog.csdn.net/kunkliu/article/details/123345233?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-1-123345233-blog-102808611.pc_relevant_3mothn_strategy_and_data_recovery&spm=1001.2101.3001.4242.2&utm_relevant_index=4

https://blog.csdn.net/PX1525813502/article/details/125016412

https://www.likecs.com/show-204244559.html#sc=3100

注意：对于任何，你可以通过、和或通过obj.x、obj.y、obj.z、obj.w 或obj.r 、obj.g 、obj.b 、obj.a 访问vec4其组件。它们是等价的；这只是一种方便的命名方式，以使你的代码更具可读性，以便其他人看到 obj.r 时，他们会理解obj代表一种颜色

*/
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QTimer>
#include <QOpenGLFunctions>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)

class GLYuvWidget  : public QOpenGLWidget,QOpenGLFunctions
{
    Q_OBJECT
public:
    GLYuvWidget(QWidget* parent =nullptr);
    ~GLYuvWidget();
    QWidget* setParentWidget(QWidget* parent);

public slots:
    void slotShowYuv(uchar *ptr,uint width,uint height); //显示一帧Yuv图像

protected:
    void initializeGL() ;
    void paintGL() ;

private:
    void drawYUV420p();
    void drawYUV422p();
    QOpenGLShaderProgram *program;
    QOpenGLBuffer vbo;
    GLuint textureUniformY,textureUniformU,textureUniformV,textFrame; //opengl中y、u、v分量位置
    QOpenGLTexture *textureY = nullptr,*textureU = nullptr,*textureV = nullptr;
    QOpenGLShader *vshader=nullptr,*fshader=nullptr;
    GLuint idY,idU,idV; //自己创建的纹理对象ID，创建错误返回0
    uint videoW,videoH;
    uchar *yuvPtr = nullptr;
    QWidget * widget=nullptr;
};

#endif // GLYUVWIDGET_H
