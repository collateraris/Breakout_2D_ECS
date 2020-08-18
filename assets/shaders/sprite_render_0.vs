#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aColor;
layout (location = 3) in mat4 aProjModel;

out vec2 vTexCoords;
out vec3 vColor;

void main()
{
    vTexCoords = aTex;
    vColor = aColor;
    gl_Position = aProjModel * vec4(aPos, 1.0);
}