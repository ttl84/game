#version 330 core
in vec2 fTexCoord;
out vec4 colour;

uniform sampler2D uFragTexture;
void main()
{
	vec4 texColour = texture(uFragTexture, fTexCoord);
	if(texColour.a < 1.0) {
		discard;
	}
	colour = texColour;
}
