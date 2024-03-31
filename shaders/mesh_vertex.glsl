#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 model;

varying vec3 normal;
varying vec3 fragment_pos;

void main()
{
	gl_Position = model * vec4(pos, 1.0);
}