#version 430 core

in vec2 vTexCoords;

uniform sampler2D uImage;
uniform vec3 uColor;

void main()
{   
    gl_FragColor = vec4(uColor, 1.0) * texture(uImage, vTexCoords);
} 