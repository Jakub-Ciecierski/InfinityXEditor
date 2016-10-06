#ifndef DUCK_EBO_H
#define DUCK_EBO_H

#include <GL/glew.h>
#include <vector>

class EBO {
private:
    GLuint id;
    const std::vector<GLuint>* indices;

public:

    EBO(const std::vector<GLuint>* indices);

    ~EBO();

    void bind(GLenum usage = GL_STATIC_DRAW);
    void unbind();
};


#endif //DUCK_EBO_H
