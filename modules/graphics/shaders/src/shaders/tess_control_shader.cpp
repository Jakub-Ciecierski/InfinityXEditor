#include "shaders/tess_control_shader.h"

TessControlShader::TessControlShader(std::string shaderSource) :
    Shader(shaderSource){

}

TessControlShader::~TessControlShader() {

}

GLuint TessControlShader::createShader() {
    return glCreateShader(GL_TESS_CONTROL_SHADER);
}
