#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;       //sampler2D,采样器
uniform sampler2D ourTexture2;

uniform float op;
void main()
{
//    color = texture(ourTexture, TexCoord1); //来采集纹理的颜色，第一个参数是纹理采样器，第二个参数对应的纹理坐标

    //根据第三个参数进行线性插值,0.2表示返回80%第一个输入颜色，和20%第二个输入颜色
    color = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),op);
}
