#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aOffset;

out vec2 vTexCoords;
out vec4 vParticleColor;

uniform mat4 uProjection;

void main()
{
    float scale = 10.0f;
    vTexCoords = aTex;
    vParticleColor = aColor;
    vec3 particlePos = vec3(aPos.xy * scale + aOffset, 0.0);
    gl_Position = uProjection * vec4(particlePos, 1.0);
}