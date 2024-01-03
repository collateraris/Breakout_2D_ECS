#version 430 core

layout (location = 0) out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D uScene;

void main()
{   
    FragColor = vec4(1.0 - texture(uScene, vTexCoords).rgb, 1.0);
} 