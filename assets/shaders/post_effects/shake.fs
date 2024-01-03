#version 430 core

layout (location = 0) out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D uScene;
#define KERNEL_SIZE 9
uniform vec2  uOffsets[KERNEL_SIZE];
uniform float uBlurKernel[KERNEL_SIZE];

void main()
{   
    vec4 color = vec4(0);
    for(int i = 0; i < KERNEL_SIZE; i++)
    {
        vec3 sceneOffset = texture(uScene, vTexCoords.st + uOffsets[i]).rgb;
        sceneOffset *= uBlurKernel[i];
        color += vec4(sceneOffset, 0.);
    }
    color.a = 1.0;

   FragColor = color;
} 