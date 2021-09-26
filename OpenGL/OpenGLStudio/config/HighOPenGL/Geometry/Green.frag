#version 330 core
in vec3 fColor;//输出颜色向量
out vec4 FragColor;

void main()
{
    FragColor = vec4(fColor,1.0);
}
