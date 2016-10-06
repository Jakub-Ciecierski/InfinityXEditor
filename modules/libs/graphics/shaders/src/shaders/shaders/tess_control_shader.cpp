#include "shaders/shaders/tess_control_shader.h"

TessControlShader::TessControlShader(std::string shaderSource,
                                     std::string file_path) :
    Shader(shaderSource, file_path){
}

TessControlShader::TessControlShader(const TessControlShader& other) :
    Shader(other){

}

TessControlShader::~TessControlShader() {

}

GLuint TessControlShader::createShader() {
    return glCreateShader(GL_TESS_CONTROL_SHADER);
}
