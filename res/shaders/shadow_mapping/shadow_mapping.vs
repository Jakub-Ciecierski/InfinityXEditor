#version 400 core

/**
 * Shadow Mapping. Transform position of each vertex into light space and then
 * saves the resulting depth buffer to texture (done by FBO).
 */

layout (location = 0) in vec3 position;

out vec2 vTexCoords;

// Object's Model
uniform mat4 ModelMatrix;
// Transforms vertex to light space
uniform mat4 LightSpaceMatrix;

void main() {
    gl_Position = LightSpaceMatrix * ModelMatrix * vec4(position, 1.0f);
}