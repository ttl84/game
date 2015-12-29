#version 330 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 vTexCoord;

uniform mat4 transform;

out vec2 fTexCoord;

void main()
{
	gl_Position =  transform * vec4(inPosition, 1.0);

	fTexCoord = vTexCoord;
}
