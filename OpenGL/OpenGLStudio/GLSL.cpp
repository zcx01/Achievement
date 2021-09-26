#include "GLSL.h"
#include <QOpenGLFunctions>
#include <QDebug>
#include <GL/gl.h>


GLSL::GLSL()
    : OpenGLWindow()
{
}

GLSL::~GLSL()
{

}

void GLSL::resizeEvent(QResizeEvent *)
{

}

void GLSL::initialize()
{

    //----------------------------------------创建顶点着色器-----------------------------------------
    //创建顶点着色器
    /*
     * GL_VERTEX_SHADER:顶点着色器
     * GL_FRAGMENT_SHADER:片段着色器
     * */
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //把这个着色器源码附加到着色器对象上
    const char *vertexShaderSource ="#version 330 core\n\
            layout (location = 0) in vec3 position;\
            layout (location = 1) in vec3 color;\
            out vec3 ourColor;\
    void main()\
    {\
        gl_Position = vec4(position.x, position.y, position.z, 1.0);\
        ourColor = color;\
    }";

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //编译已存储在shader指定的着色器对象中的源代码字符串
    glCompileShader(vertexShader);

    //检查是否成功
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        qDebug()<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED vertexShader" << infoLog ;
    }

    //--------------------------------------片段着色器---------------------------------------------
    static const char *fragmentShaderSource ="#version 330 core\n\
            in vec3 ourColor;\
            out vec4 color;\
    \
    void main()\
    {\
        color = vec4(ourColor,1.0f);\
    }";

    GLuint fragementShader;
    fragementShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragementShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragementShader);

    //检查是否成功
    glGetShaderiv(fragementShader,GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        qDebug()<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED fragementShader" << infoLog ;
    }

    //------------------------------------着色器程序-------------------------------------------
    //-----------------------------------把两个着色器链接到一个用来渲染的着色器程序中-----------

    //创建一个程序对象
    shaderProgram = glCreateProgram();

    //把之情编译的着色器附加到程序对象上，在链接它们
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragementShader);
    //链接
    glLinkProgram(shaderProgram);

    //检查是否有错误
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        qDebug()<< "ERROR::SHADER::VERTEX::COMPILATION_FAILED shaderProgram" << infoLog ;
    }

    //激活对象，此函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象
    glUseProgram(shaderProgram);

    //删除着色器对象, 把着色器对象链接到程序对象以后，要删除掉
    glDeleteShader(vertexShader);
    glDeleteShader(fragementShader);
}

void GLSL::render()
{

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

//    drawRect();

    drawTriangle();

}

void GLSL::drawTriangle()
{
    GLfloat vertices[] = {
        // 位置              // 颜色
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };

    //-----------------VAO(顶点数组对象、存储所有的状态)---------------------
    //创建VA0
    GLuint VAO;
    glGenVertexArrays(1,&VAO);

    //绑定VAO
    glBindVertexArray(VAO);


    //-----------------VBO(顶点缓冲对象)--------------------------------------------
    //生成一个对象
    GLuint VBO;
    glGenBuffers(1, &VBO);


    //--------------------------设置顶点缓冲数据---------------------------------
    //绑定缓冲
    /*
    GL_ARRAY_BUFFER         ：顶点缓冲对象
    GL_ELEMENT_ARRAY_BUFFER ：索引缓冲对象
    */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //设置缓冲内存的数据
    /*
     *参数1:目标缓冲的类型
     *参数2:指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行
     *参数3:参数是我们希望发送的实际数据
     *
     *参数4:指定了我们希望显卡如何管理给定的数据。它有三种形式：
     *GL_STATIC_DRAW ：数据不会或几乎不会改变。
     *GL_DYNAMIC_DRAW：数据会被改变很多。
     *GL_STREAM_DRAW ：数据每次绘制时都会改变。
    */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //---------------------------------------链接顶点属性----------------------------------
    //告诉OPenGL该如何解释顶点数据
    //参数1:指定我们要配置的顶点属性   [因为顶点着色器源码中有<layout(location = 0)>定义了position顶点位置为0]
    //参数2:指定顶点属性的大小         [顶点属性是一个vec3，它由3个值组成，所以大小是3]
    //参数3:参数指定数据的类型
    //参数4:是否数据标准化               [如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间]
    //参数5:步长,连续的顶点属性组之间的间隔   [由于下个组位置数据在3个GLfloat之后，我们把步长设置为3 * sizeof(GLfloat)],如果是精密排列的，也可以设置0
    //参数6:表示位置数据在缓冲中起始位置的偏移量 [由于位置数据在数组的开头，所以这里是0]

    //位置属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 6 * sizeof(GLfloat),(GLvoid*)0);
    //以顶点属性位置值作为参数，启用顶点属性 默认是顶点属性是禁用的
    glEnableVertexAttribArray(0);

    //颜色属性
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 6 * sizeof(GLfloat),(GLvoid*)( 3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    //解绑VAO
    glBindVertexArray(0);


    //------------------------绘制
    glBindVertexArray(VAO);
    //使用当前激活的着色器，之情定义的顶点属性配置，和VBO的顶点数据来绘制图元
    //参数1:绘制的图元类型   GL_TRIANGLES(三角形)
    //参数2:顶点数组的起始索引
    //参数3:一共绘制多少个顶点
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

//要添加一个索引缓冲器，使用glDrawElements代替glDrawArrays
void GLSL::drawRect()
{
    GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    GLuint indices[] = { // 注意索引从0开始!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };


    //-----------------VAO(顶点数组对象、存储所有的状态)---------------------
    //创建VA0
    GLuint VAO;
    glGenVertexArrays(1,&VAO);

    //绑定VAO
    glBindVertexArray(VAO);


    //-----------------VBO(顶点缓冲对象)--------------------------------------------
    //生成一个对象
    GLuint VBO;
    glGenBuffers(1, &VBO);

    //-----------------------------------索引缓冲对象----------------------
    GLuint EBO;
    glGenBuffers(1,&EBO);


    //--------------------------设置顶点缓冲数据---------------------------------
    //绑定缓冲
    /*
    GL_ARRAY_BUFFER         ：顶点缓冲对象
    GL_ELEMENT_ARRAY_BUFFER ：索引缓冲对象
    */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //设置缓冲内存的数据
    /*
     *参数1:目标缓冲的类型
     *参数2:指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行
     *参数3:参数是我们希望发送的实际数据
     *
     *参数4:指定了我们希望显卡如何管理给定的数据。它有三种形式：
     *GL_STATIC_DRAW ：数据不会或几乎不会改变。
     *GL_DYNAMIC_DRAW：数据会被改变很多。
     *GL_STREAM_DRAW ：数据每次绘制时都会改变。
    */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //---------------------设置索引缓冲数据-----------------------------
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


    //---------------------------------------链接顶点属性----------------------------------
    //告诉OPenGL该如何解释顶点数据
    //参数1:指定我们要配置的顶点属性   [因为顶点着色器源码中有<layout(location = 0)>定义了position顶点位置为0]
    //参数2:指定顶点属性的大小         [顶点属性是一个vec3，它由3个值组成，所以大小是3]
    //参数3:参数指定数据的类型
    //参数4:是否数据标准化               [如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间]
    //参数5:步长,连续的顶点属性组之间的间隔   [由于下个组位置数据在3个GLfloat之后，我们把步长设置为3 * sizeof(GLfloat)],如果是精密排列的，也可以设置0
    //参数6:表示位置数据在缓冲中起始位置的偏移量 [由于位置数据在数组的开头，所以这里是0]
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(GLfloat),(GLvoid*)0);

    //以顶点属性位置值作为参数，启用顶点属性 默认是顶点属性是禁用的
    glEnableVertexAttribArray(0);

    //解绑VAO
    glBindVertexArray(0);

    //绘制多边形的模式
    //参数1:应用到所有的三角形的正面和背面
    //参数2:模式
    //      GL_LINE:线框模式
    //      GL_FILL:填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //------------------------绘制
    glBindVertexArray(VAO);

    //参数1:指定我们绘制的模式
    //参数2:绘制顶点的格式
    //参数3:索引的类型
    //参数4:指定EBO中的偏移量
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

    glBindVertexArray(0);

}
