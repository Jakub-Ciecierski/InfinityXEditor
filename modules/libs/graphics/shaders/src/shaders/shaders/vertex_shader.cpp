#include "shaders/shaders/vertex_shader.h"

using namespace std;

VertexShader::VertexShader(string shaderSource) :
        Shader(shaderSource){

}

VertexShader::~VertexShader() {

}

GLuint VertexShader::createShader() {
    return glCreateShader(GL_VERTEX_SHADER);
}
