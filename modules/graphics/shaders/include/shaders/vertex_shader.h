#ifndef DUCK_VERTEX_SHADER_H
#define DUCK_VERTEX_SHADER_H

#include "shaders/shader.h"

class VertexShader : public Shader{
private:

protected:
    virtual GLuint createShader() override;

public:

    VertexShader(std::string shaderSource);

    ~VertexShader();

};


#endif //DUCK_VERTEX_SHADER_H
