#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 vTexCoords;

uniform float uTime;

void main()
{
    vec2 texture = aTex;
    gl_Position = vec4(aPos, 1.0f);

    float strength = 0.3;
    vec2 pos = vec2(texture.x + sin(uTime) * strength, texture.y + cos(uTime) * strength);        
    vTexCoords = pos;
}