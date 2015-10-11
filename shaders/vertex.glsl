#version 330 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColour;

uniform vec3 ourColour;
out vec3 vertexColour;
void main()
{
	gl_Position.xyz = inPosition + ourColour;
	gl_Position.w = 1.0;

	vertexColour = inColour + ourColour;
}
