#ifndef DUCK_FRAGMENT_SHADER_H
#define DUCK_FRAGMENT_SHADER_H

#include "shaders/shader.h"

class FragmentShader : public Shader{
private:

protected:
    virtual GLuint createShader();

public:
    FragmentShader(std::string shaderSource,
                   std::string file_path);
    FragmentShader(const FragmentShader& other);

    ~FragmentShader();

};


#endif //DUCK_FRAGMENT_SHADER_H
