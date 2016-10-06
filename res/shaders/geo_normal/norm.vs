#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 binormal;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    vec4 pos4 = vec4(position, 1.0f);
    mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    gl_Position = MVP * pos4;

    // http://learnopengl.com/
    // To accommodate for scaling and rotations
    // we'll transform the normals first with a normal matrix before
    // transforming it to clip-space coordinates (geometry shader receives its
    // position vectors as clip-space coordinates so we should also transform
    // the normal vectors to the same space).
    mat3 normalMatrix = mat3(transpose(inverse(ViewMatrix * ModelMatrix)));
    vs_out.normal = normalize(vec3(ProjectionMatrix * vec4(normalMatrix * normal, 1.0)));
}