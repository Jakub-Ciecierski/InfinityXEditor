#include "shaders/shaders/tess_eval_shader.h"

TessEvalShader::TessEvalShader(std::string shaderSource,
                               std::string file_path) :
        Shader(shaderSource, file_path){
}

TessEvalShader::TessEvalShader(const TessEvalShader& other) :
    Shader(other){

}

TessEvalShader::~TessEvalShader() {

}

GLuint TessEvalShader::createShader() {
    return glCreateShader(GL_TESS_EVALUATION_SHADER);
}
