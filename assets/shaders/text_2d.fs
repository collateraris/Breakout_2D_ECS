#version 430 core

in vec2 vTexCoords;

uniform sampler2D uText;
uniform vec3 uTextColor;

void main()
{   
    gl_FragColor = vec4(uTextColor, 1.) * texture(uText, vTexCoords);
} 