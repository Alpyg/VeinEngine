#version 400 core
layout(location = 0) out vec4 color;

in vec2 v_UV;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_UV);
	color = vec4(1.0);
}