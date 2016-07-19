#ifndef DUCK_VAO_H
#define DUCK_VAO_H

#include <GL/gl.h>
#include "model/buffers/vbo.h"
#include "model/buffers/ebo.h"

class VAO {
private:
    GLuint id;
public:

    VAO();

    ~VAO();

    void bindBuffers(VBO &vbo, EBO &ebo);

    void bind();
    void unbind();
};


#endif //DUCK_VAO_H
