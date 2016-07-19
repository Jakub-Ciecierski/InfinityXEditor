#include <mesh/mesh_data.h>
#include "model/buffers/vbo.h"

#include <GL/glew.h>
#include <iostream>

using namespace std;

VBO::VBO(const std::vector<Vertex>* vertices) :
        vertices(vertices){
    glGenBuffers(1, &vboID);
}

VBO::~VBO() {
    glDeleteBuffers(1, &vboID);
}

void VBO::bind(GLenum usage) {
    GLuint bytesCount = sizeof(Vertex) * vertices->size();

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, bytesCount,
                 vertices->data(), usage);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
