#version 430 core

in vec2 vTexCoords;
in vec4 vParticleColor;

uniform sampler2D uSprite;

void main()
{   
    gl_FragColor = vParticleColor * texture(uSprite, vTexCoords);
} 