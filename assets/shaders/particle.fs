#version 430 core

layout (location = 0) out vec4 FragColor;

in vec2 vTexCoords;
in vec4 vParticleColor;

uniform sampler2D uSprite;


void main()
{   
    FragColor = vParticleColor * texture(uSprite, vTexCoords);
} 