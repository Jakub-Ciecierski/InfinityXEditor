#ifndef TESELATION_TESS_EVAL_SHADER_H
#define TESELATION_TESS_EVAL_SHADER_H

#include <rendering/shaders/shader.h>

class TessEvalShader : public Shader{
private:

protected:
    virtual GLuint createShader() override;

public:

    TessEvalShader(std::string shaderSource);

    ~TessEvalShader();

};


#endif //TESELATION_TESS_EVAL_SHADER_H
