#include "shaders/shaders/fragment_shader.h"

using namespace std;

FragmentShader::FragmentShader(string shaderSource,
                               std::string file_path) :
        Shader(shaderSource, file_path){
}

FragmentShader::FragmentShader(const FragmentShader& other)
        : Shader(other){

}

FragmentShader::~FragmentShader() {

}

GLuint FragmentShader::createShader() {
    return glCreateShader(GL_FRAGMENT_SHADER);
}

