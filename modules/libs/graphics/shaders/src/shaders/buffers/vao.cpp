#include <GL/glew.h>

#include "shaders/buffers/vao.h"

VAO::VAO(){
    glGenVertexArrays(1, &id);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &id);
}

void VAO::bindVertexBuffers(VBO &vbo, EBO &ebo){
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

    vbo.unbind();
    this->unbind();
}

void VAO::bindInstancedRenderingBuffers(InstancedData& instanced_data){
    GLuint byte_size
            = instanced_data.model_matrices.size() * sizeof(glm::mat4);

    this->bind();

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, byte_size,
                 instanced_data.model_matrices.data(), GL_STATIC_DRAW);

    // Set attribute pointers for matrix (4 times vec4)
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (GLvoid*)0);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (GLvoid*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (GLvoid*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(8);
    glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (GLvoid*)(3 * sizeof(glm::vec4)));

    // Notify instanced rendering
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);
    glVertexAttribDivisor(8, 1);

    this->unbind();
}

void VAO::bind() {
    glBindVertexArray(id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}
