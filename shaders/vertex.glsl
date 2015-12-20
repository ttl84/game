#version 330 core
layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 vTexCoord;

uniform mat3 transform;

out vec2 fTexCoord;
void main()
{
	gl_Position.xyz =  transform * vec3(inPosition, 1.0);

	fTexCoord = vTexCoord;
}
