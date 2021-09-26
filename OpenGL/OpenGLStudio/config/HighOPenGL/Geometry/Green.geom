#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

in VS_OUT {
	vec3 color;
}gs_in[];//�Ӷ�����ɫ�����������������ǻ����������ʽ��ʾ����

out vec3 fColor;//�����ɫ����

void build_house(vec4 position)
{    
	fColor = gs_in[0].color; // gs_in[0] ��Ϊֻ��һ�����붥��
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:����
    EmitVertex();   
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:����
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:����
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:����
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:����
	fColor = vec3(1.0, 1.0, 1.0);
    EmitVertex();
    EndPrimitive();
}

void main() {    
    build_house(gl_in[0].gl_Position);
}
