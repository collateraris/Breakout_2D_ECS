#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 vTexCoords;

uniform float uTime;

void main()
{
    vTexCoords = vec2(1.0 - aTex.x, 1.0 - aTex.y);
    gl_Position = vec4(aPos, 1.0f);
}