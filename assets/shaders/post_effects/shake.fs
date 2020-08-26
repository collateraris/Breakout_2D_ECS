#version 430 core

in vec2 vTexCoords;

uniform sampler2D uScene;
#define KERNEL_SIZE 9
uniform vec2  uOffsets[KERNEL_SIZE];
uniform int   uBlurKernel[KERNEL_SIZE];

void main()
{   
    vec4 color = vec4(0);
    for(int i = 0; i < KERNEL_SIZE; i++)
    {
        vec3 sceneOffset = texture(uScene, vTexCoords.st + uOffsets[i]).rgb;
        color += vec4(sceneOffset * uBlurKernel[i], 0.0);
    }
    color.a = 1.0;

    gl_FragColor = color;
} 