#version 330 core
layout (location = 0) in vec3 pos;
uniform mat4 model;

out vec3 position;

void main()
{
	gl_Position = model * vec4(pos, 1.0);
	position = pos.xyz;
}