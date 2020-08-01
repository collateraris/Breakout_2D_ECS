#version 430 core

layout(location = 0) out vec4 color;

in vec2 vTexCoords;

uniform sampler2D uImage;
uniform vec3 uColor;

void main()
{    
    color = vec4(uColor, 1.0) * texture(uImage, vTexCoords);
} 