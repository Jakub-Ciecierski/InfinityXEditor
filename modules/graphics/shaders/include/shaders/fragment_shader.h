#ifndef DUCK_FRAGMENT_SHADER_H
#define DUCK_FRAGMENT_SHADER_H

#include "shaders/shader.h"

class FragmentShader : public Shader{
private:

protected:
    virtual GLuint createShader();

public:
    FragmentShader(std::string shaderSource);

    ~FragmentShader();

};


#endif //DUCK_FRAGMENT_SHADER_H
