#include "shaders/shaders/geometry_shader.h"

using namespace std;

GeometryShader::GeometryShader(string shaderSource,
                               std::string file_path) :
        Shader(shaderSource, file_path){
}

GeometryShader::GeometryShader(const GeometryShader& other)
        : Shader(other){

}

GeometryShader::~GeometryShader() {

}

GLuint GeometryShader::createShader() {
    return glCreateShader(GL_GEOMETRY_SHADER);
}

