#ifndef TESELATION_TESS_EVAL_SHADER_H
#define TESELATION_TESS_EVAL_SHADER_H

#include <shaders/shader.h>

class TessEvalShader : public Shader{
private:

protected:
    virtual GLuint createShader() override;

public:

    TessEvalShader(std::string shaderSource,
                   std::string file_path);
    TessEvalShader(const TessEvalShader& other);

    ~TessEvalShader();

};


#endif //TESELATION_TESS_EVAL_SHADER_H
