#include "rendering/shaders/loaders/shader_loader.h"

#include <rendering/shaders/vertex_shader.h>
#include <rendering/shaders/fragment_shader.h>

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

VertexShader ShaderLoader::LoadDefaultVertexShader() {
    string vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 position;\n"
            "void main()\n"
            "{\n"
            "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
            "}\0";

    return VertexShader(vertexShaderSource);
}

FragmentShader ShaderLoader::LoadDefaultFragmentShader() {
    string fragmentShaderSource = "#version 330 core\n"
            "out vec4 color;\n"
            "void main()\n"
            "{\n"
            "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

    return FragmentShader(fragmentShaderSource);
}

VertexShader ShaderLoader::loadVertexShader(const GLchar *path) {
    std::string shaderCode = getShaderCode(path);
    VertexShader vertexShader(shaderCode.c_str());

    return vertexShader;
}

FragmentShader ShaderLoader::loadFragmentShader(const GLchar *path) {
    std::string shaderCode = getShaderCode(path);

    FragmentShader fragmentShader(shaderCode.c_str());

    return fragmentShader;
}

TessControlShader ShaderLoader::loadTessControlShader(const GLchar *path) {
    std::string shaderCode = getShaderCode(path);

    TessControlShader shader(shaderCode.c_str());

    return shader;
}

TessEvalShader ShaderLoader::loadTessEvalShader(const GLchar *path) {
    std::string shaderCode = getShaderCode(path);

    TessEvalShader shader(shaderCode.c_str());

    return shader;
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