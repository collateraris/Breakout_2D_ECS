#version 430 core

in vec2 vTexCoords;
in vec3 vColor;

uniform sampler2D uImage;

void main()
{   
    gl_FragColor = vec4(vColor, 1.0) * texture(uImage, vTexCoords);
} 