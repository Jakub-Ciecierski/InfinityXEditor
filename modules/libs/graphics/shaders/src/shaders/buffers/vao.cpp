#include <GL/glew.h>

#include "shaders/buffers/vao.h"

VAO::VAO(){
    glGenVertexArrays(1, &id);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &id);
}

void VAO::bindBuffers(VBO &vbo, EBO &ebo){
    this->bind();

    vbo.bind();
    ebo.bind();

    const GLuint DATA_PER_POSITION = 3;
    const GLuint DATA_PER_NORMAL = 3;
    const GLuint DATA_PER_TEXTURE = 2;
    const GLuint DATA_PER_TANGET = 3;
    const GLuint DATA_PER_BINORMAL = 3;

    // Position
    glVertexAttribPointer(0, DATA_PER_POSITION, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, DATA_PER_NORMAL, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    // Texture
    glVertexAttribPointer(2, DATA_PER_TEXTURE, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    // Tangent
    glVertexAttribPointer(3, DATA_PER_TANGET, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, Tangent));
    glEnableVertexAttribArray(3);

    // Binormal
    glVertexAttribPointer(4, DATA_PER_BINORMAL, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, Binormal));
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->unbind();
}

void VAO::bind() {
    glBindVertexArray(id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}
