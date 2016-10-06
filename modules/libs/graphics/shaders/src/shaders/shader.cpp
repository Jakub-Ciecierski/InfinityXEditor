#include "shaders/shader.h"

#include <iostream>
#include <stdexcept>
#include <shaders/loaders/shader_loader.h>


using namespace std;

Shader::Shader(string shaderSource,
               string file_path) :
        shaderSource(shaderSource),
        file_path_(file_path){
}

Shader::Shader(const Shader& other){
    id = other.id;
    shaderSource = other.shaderSource;
    file_path_ = other.file_path_;
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

void Shader::Reload(){
    ShaderLoader shader_loader;
    shaderSource = shader_loader.getShaderCode(file_path_.c_str());

    deleteShader();
    compile();
}

GLuint Shader::getKey() {
    return id;
}

std::string Shader::getSource(){
    return this->shaderSource;
}