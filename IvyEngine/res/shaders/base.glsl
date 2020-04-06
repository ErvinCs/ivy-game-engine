#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 o_texCoord;
out vec2 o_position;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

void main()
{
	o_texCoord = texCoord;
	gl_Position = u_viewProjection * u_transform * vec4(position, 1.0);
	o_position = gl_Position.xy;
};

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec2 o_texCoord;
in vec2 o_position;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
	color = texture(u_texture, o_texCoord) * u_color;
};
