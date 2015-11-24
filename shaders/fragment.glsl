#version 330 core
in vec3 vertexColour;
out vec3 colour;

void main()
{
	colour.xy = vertexColour.xy;
	colour.z = 1.0;
}
