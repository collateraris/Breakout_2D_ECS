#version 430 core
layout (location = 0) in vec4 aVertex; // <vec2 position, vec2 texCoords>

out vec2 vTexCoords;

uniform mat4 uProjectionModel;

void main()
{
    vTexCoords = aVertex.zw;
    gl_Position = uProjectionModel * vec4(aVertex.xy, 0.0, 1.0);
}