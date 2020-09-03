#version 430 core

in vec2 vTexCoords;

uniform sampler2D uText;
uniform vec3 uTextColor;

void main()
{   
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uText, vTexCoords).r);
    gl_FragColor = vec4(uTextColor, 1.0) * sampled;
} 