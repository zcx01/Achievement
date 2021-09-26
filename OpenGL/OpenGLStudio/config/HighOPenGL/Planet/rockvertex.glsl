#version 330 core
// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aNormal;
// layout (location = 2) in vec2 aTexCoords;
// layout (location = 3) in mat4 aInstanceMatrix;	//mat4站4个vec4，所以要配置4个

// out vec2 TexCoords;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

// void main()
// {
    // TexCoords = aTexCoords;    
    // gl_Position = projection * view  *model* vec4(aPos, 1.0);
// }

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;
// layout (location = 3) in vec4 a1;
// layout (location = 4) in vec4 a2;
// layout (location = 5) in vec4 a3;
// layout (location = 6) in vec4 a4;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view  * aInstanceMatrix * vec4(aPos, 1.0f); 
}