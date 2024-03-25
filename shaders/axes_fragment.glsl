#version 330 core
in vec3 position;
out vec4 pixel_color;

void main()
{
	if(position.z > 0)
		pixel_color = vec4(0, 0, 1, 1);
	if(position.y > 0)
		pixel_color = vec4(0, 1, 0, 1);
	if(position.x > 0)
		pixel_color = vec4(1, 0, 0, 1);
}