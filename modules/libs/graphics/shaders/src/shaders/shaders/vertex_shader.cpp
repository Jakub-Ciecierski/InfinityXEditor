#include "shaders/shaders/vertex_shader.h"

using namespace std;

VertexShader::VertexShader(string shaderSource,
                           std::string file_path) :
        Shader(shaderSource, file_path){
}

VertexShader::VertexShader(const VertexShader& other) :
    Shader(other){

}

VertexShader::~VertexShader() {

}

GLuint VertexShader::createShader() {
    return glCreateShader(GL_VERTEX_SHADER);
}
