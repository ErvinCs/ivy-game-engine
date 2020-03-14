#shader vertex
#version 440 core

layout(location = 0) in vec3 position;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

void main()
{
	gl_Position = u_viewProjection * u_transform * vec4(position, 1.0);
}

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main()
{
	color = u_color;
}
