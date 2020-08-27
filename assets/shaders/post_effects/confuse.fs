#version 430 core

in vec2 vTexCoords;

uniform sampler2D uScene;

void main()
{   
    gl_FragColor = vec4(1.0 - texture(uScene, vTexCoords).rgb, 1.0);
} 