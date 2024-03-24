#version 330 core
varying vec3 normal;
varying vec3 fragment_pos;

uniform vec3 part_color;
uniform vec3 light_position;
out vec4 fragment_color;

const float reflection_coefficient = 0.5;

void main()
{
	// vec3 light_color = vec3(1.0, 1.0, 1.0);	
	// vec3 lpos = light_position;
		
	// vec4 ov_pos = vec4(light_position * 25, 1.0);
	// float level = dot(normal, normalize(ov_pos.xyz - fragment_pos)) * reflection_coefficient;
	// vec3 diff_comp = level * light_color;
	fragment_color = vec4(1.0, 0, 0, 1.0);
}