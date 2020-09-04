#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 vTexCoords;

uniform mat4 uProjection;

void main()
{
    vTexCoords = aTex;
    gl_Position = uProjection * vec4(aPos, 1.0);
}