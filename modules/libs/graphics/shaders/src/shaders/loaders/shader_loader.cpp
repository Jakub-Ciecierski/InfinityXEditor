#include "shaders/loaders/shader_loader.h"

#include <shaders/vertex_shader.h>
#include <shaders/fragment_shader.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <stdexcept>

using namespace std;

ShaderLoader::ShaderLoader(){

}

ShaderLoader::~ShaderLoader() {

}

VertexShader* ShaderLoader::loadVertexShader(const GLchar *path) {
    std::string shaderCode = getShaderCode(path);
    return new VertexShader(shaderCode.c_str(), std::string(path));
}

GeometryShader* ShaderLoader::loadGeometryShader(const GLchar* path){
    std::string shaderCode = getShaderCode(path);
    return new GeometryShader(shaderCode.c_str(), std::string(path));
}

FragmentShader* ShaderLoader::loadFragmentShader(const GLchar *path) {
    std::string shaderCode = getShaderCode(path);
    return new FragmentShader(shaderCode.c_str(), std::string(path));
}

TessControlShader* ShaderLoader::loadTessControlShader(const GLchar *path) {
    std::string shaderCode = getShaderCode(path);
    return new TessControlShader(shaderCode.c_str(), std::string(path));
}

TessEvalShader* ShaderLoader::loadTessEvalShader(const GLchar *path) {
    std::string shaderCode = getShaderCode(path);
    return new TessEvalShader(shaderCode.c_str(),std::string(path));
}

std::string ShaderLoader::getShaderCode(const GLchar *path) {
    std::string code;
    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::badbit);
    try{
        shaderFile.open(path);
        if(!shaderFile.is_open()){
            std::string info = "No such file: " + std::string(path);
            throw std::invalid_argument(info);
        }

        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        code = shaderStream.str();
    }
    catch (std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    if(code.empty()){
        std::string info = "Empty file: " + std::string(path);
        throw std::invalid_argument(info);
    }

    return code;
}