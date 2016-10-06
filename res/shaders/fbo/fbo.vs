#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 binormal;

out vec2 vTexCoords;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
    vTexCoords = texCoords;
}