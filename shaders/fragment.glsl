#version 330 core
in vec3 vertexColour;
in vec2 fragTexCoord;
out vec4 colour;

uniform sampler2D uFragTexture;
void main()
{
	vec4 texColour = texture(uFragTexture, fragTexCoord);
	if(texColour.a < 1.0) {
		discard;
	}
	colour = texColour;
}
