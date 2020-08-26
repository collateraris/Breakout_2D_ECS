#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 vTexCoords;

uniform float uTime;

void main()
{
    vTexCoords = aTex;
    float strength = 0.01;
    gl_Position.x += cos(uTime * 10) * strength;        
    gl_Position.y += cos(uTime * 15) * strength; 
}