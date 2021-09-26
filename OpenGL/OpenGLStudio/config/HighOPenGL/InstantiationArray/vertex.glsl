#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;

out vec3 fColor;

void main()
{
	//第一个四边形的实例会非常小，随着绘制实例的增加，gl_InstanceID会越来越接近100，四边形也就越来越接近原始大小
	vec2 pos = aPos * (gl_InstanceID / 100.0);
	
	gl_Position = vec4(pos+aOffset,0.0,1.0);
	fColor = aColor;
}

