#version 330 core
out vec4 FragColor;


in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;
void main()
{
    //光线/视线从空气进入玻璃
    //1.00是空气的折射率，1.52是玻璃的折射率
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(Position - cameraPos);
    vec3 R = refract(I,normalize(Normal),ratio);
    FragColor = vec4(textureCube(skybox,R).rgb,1.0f);
}
