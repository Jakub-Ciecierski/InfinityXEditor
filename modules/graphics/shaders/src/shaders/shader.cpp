#include "shaders/shader.h"

#include <iostream>
#include <stdexcept>


using namespace std;

Shader::Shader(string shaderSource){
    this->shaderSource = shaderSource;
}

Shader::~Shader() {

}

void Shader::compile() {
    id = createShader();
    const GLchar* rawData = shaderSource.c_str();
    
    glShaderSource(id, 1, &(rawData), NULL);
    glCompileShader(id);

    // Check status;
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::string infoLogStr = infoLog;
        std::cout << infoLogStr << std::endl;
        throw new std::invalid_argument("ERROR::SHADER::COMPILATION_FAILED\n"
                                        + infoLogStr);
    }
}

void Shader::deleteShader() {
    glDeleteShader(id);
}

GLuint Shader::getKey() {
    return id;
}

std::string Shader::getSource(){
    return this->shaderSource;
}