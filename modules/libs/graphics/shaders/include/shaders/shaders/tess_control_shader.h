#ifndef TESELATION_TESS_CONTROL_SHADER_H
#define TESELATION_TESS_CONTROL_SHADER_H

#include <shaders/shader.h>

class TessControlShader : public Shader {
private:

protected:
    virtual GLuint createShader() override;

public:

    TessControlShader(std::string shaderSource,
                      std::string file_path);
    TessControlShader(const TessControlShader& other);

    ~TessControlShader();

};


#endif //TESELATION_TESS_CONTROL_SHADER_H
