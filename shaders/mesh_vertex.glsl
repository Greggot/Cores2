#version 330 core
layout (location = 0) in vec3 pos;
// layout (location = 1) in vec3 norm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec3 normal;
varying vec3 fragment_pos;

void main()
{
	gl_Position = vec4(pos, 1.0);
	// gl_Position = projection * view * model * vec4(pos, 1.0);
	
	// normal = norm;
	// fragment_pos = vec3(model * vec4(pos, 1.0));
	// fragment_pos = pos;
}