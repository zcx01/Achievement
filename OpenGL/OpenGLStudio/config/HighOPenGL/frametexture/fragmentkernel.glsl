#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300.0;
const int num = 9;
void main()
{
    //我们首先为周围的纹理坐标创建了一个9个vec2偏移量的数组
    vec2 offsets[num] = vec2[](
            vec2(-offset,  offset), // 左上
            vec2( 0.0f,    offset), // 正上
            vec2( offset,  offset), // 右上
            vec2(-offset,  0.0f),   // 左
            vec2( 0.0f,    0.0f),   // 中
            vec2( offset,  0.0f),   // 右
            vec2(-offset, -offset), // 左下
            vec2( 0.0f,   -offset), // 正下
            vec2( offset, -offset)  // 右下
            );
    //定义一个核，这是一个锐化(Sharpen)核，它会锐化周围的所有像素颜色值，
    //其中的数字加起来为1
    float kernel[num] = float[](
         -1, -1, -1,
         -1,  9, -1,
         -1, -1, -1
     );
    //将每个偏移量加到当前纹理坐标上，获取需要采样的纹理，采样周围的所有像素
    vec3 sampleTex[9];
    for(int i = 0; i < num; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture,TexCoords.st+offsets[i]));
    }

    //纹理值乘以加权的核值
    vec3 col = vec3(0.0);
    for(int i = 0; i < num; i++)
        col += sampleTex[i] * kernel[i];
    FragColor = vec4(col, 1.0);
}
