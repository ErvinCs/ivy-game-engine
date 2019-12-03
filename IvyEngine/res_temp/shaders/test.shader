#version 440 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_vpm;

out vec3 v_Position;
out vec4 v_Color;

void main()
{
	v_Position = a_Position;
	v_Color = a_Color;
	gl_Position = u_vpm * vec4(a_Position, 1.0);
}


#version 440 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;

void main()
{
	color = vec4(v_Position * 0.5 + 0.5, 1.0);
	color = v_Color;
}
