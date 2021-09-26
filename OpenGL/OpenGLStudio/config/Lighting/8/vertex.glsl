#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal;  //法向量---（传递给片段着色器）
layout (location = 2) in vec2 aTexCoords;

out vec3 Normal;
out vec3 FragPos;   //顶点在世界坐标上的位置
out vec2 TexCoords;

uniform mat4 model;         //模型矩阵-----(从局部坐标转换到世界坐标)
uniform mat4 view;          //观察矩阵
uniform mat4 projection;    //投影矩阵
void main()
{
    //使用inverse和transpose函数自己生成这个法线矩阵,移除对法向量错误缩放的影响
    Normal = mat3(transpose(inverse(model))) * aNormal;

    //局部坐标到世界坐标的转换
    FragPos =vec3(model * vec4(position,1.0f));

    gl_Position = projection*view * vec4(FragPos, 1.0f);

    TexCoords = aTexCoords;
}

