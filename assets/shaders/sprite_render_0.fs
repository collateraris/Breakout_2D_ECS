#version 430 core

layout (location = 0) out vec4 FragColor;

in vec2 vTexCoords;
in vec3 vColor;

uniform sampler2D uImage;

void main()
{   
    FragColor = vec4(vColor, 1.0) * texture(uImage, vTexCoords);
} 