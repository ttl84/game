#version 330 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in mat4 modelMatrix;
// location 3 reserved
// location 4 reserved
// location 5 reserved

uniform mat4 transform;

out vec2 fTexCoord;

void main()
{
	gl_Position =  transform * modelMatrix * vec4(inPosition, 1.0);

	fTexCoord = vTexCoord;
}
