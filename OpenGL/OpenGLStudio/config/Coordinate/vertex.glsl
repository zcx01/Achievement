#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;

//uniform mat4 transform;

uniform mat4 model;         //模型矩阵-----(从局部坐标转换到世界坐标)
uniform mat4 view;          //观察矩阵
uniform mat4 projection;    //投影矩阵
void main()
{
    //从右向左读 (每个矩阵被运算的顺序是相反的)
    gl_Position = projection*view*model  * vec4(position, 1.0f);
    ourColor = color;
    TexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}

