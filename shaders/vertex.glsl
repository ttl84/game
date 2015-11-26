#version 330 core
layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 vTexCoord;

uniform vec3 ourColour;
out vec3 vertexColour;
out vec2 fragTexCoord;
void main()
{
	gl_Position.xy = inPosition + ourColour.xy;
	gl_Position.z = 1.0;

	vertexColour = ourColour;

	fragTexCoord = vTexCoord;
}
