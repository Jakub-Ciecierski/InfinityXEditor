#include "shaders/buffers/ebo.h"

EBO::EBO(const std::vector<GLuint>* indices) :
        indices(indices){
    glGenBuffers(1, &id);
}

EBO::~EBO() {
    glDeleteBuffers(1, &id);
}

void EBO::bind(GLenum usage) {
    const GLuint* rawData = indices->data();
    GLuint bytesCount = sizeof(GLuint) * indices->size();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesCount, rawData, usage);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
