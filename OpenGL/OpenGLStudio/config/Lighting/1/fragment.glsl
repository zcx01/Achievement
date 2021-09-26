#version 330 core

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    color = vec4(objectColor * lightColor , 1.0);
//    float ambientStrength = 0.1;
//    vec3 ambient = ambientStrength * lightColor;

//    vec3 result = ambient * objectColor;
//    color = vec4(result, 1.0);
}

