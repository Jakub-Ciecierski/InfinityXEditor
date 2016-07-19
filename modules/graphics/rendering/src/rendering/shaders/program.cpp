#include "rendering/shaders/program.h"

#include <stdexcept>
#include <iostream>

Program::Program(){

}

Program::Program(VertexShader &vertexShader, FragmentShader &fragmentShader) {
    linkShaders(vertexShader, fragmentShader);
}

Program::Program(VertexShader& vertexShader, FragmentShader& fragmentShader,
                 TessControlShader& tessControlShader,
                 TessEvalShader& tessEvalShader){
    linkShaders(vertexShader, fragmentShader,
                tessControlShader, tessEvalShader);
}

Program::~Program() {

}

void Program::linkShaders(VertexShader &vertexShader,
                          FragmentShader &fragmentShader) {
    id = glCreateProgram();

    glAttachShader(id, vertexShader.getKey());
    glAttachShader(id, fragmentShader.getKey());
    glLinkProgram(id);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::string infoLogStr = infoLog;
        std::cout << infoLogStr << std::endl;
        throw new std::invalid_argument("ERROR::PROGRAM::COMPILATION_FAILED\n"
        + infoLogStr);
    }

    vertexShader.deleteShader();
    fragmentShader.deleteShader();
}

void Program::linkShaders(VertexShader &vertexShader,
                          FragmentShader &fragmentShader,
                          TessControlShader& tessControlShader,
                          TessEvalShader& tessEvalShader) {
    id = glCreateProgram();

    glAttachShader(id, vertexShader.getKey());
    glAttachShader(id, fragmentShader.getKey());
    glAttachShader(id, tessControlShader.getKey());
    glAttachShader(id, tessEvalShader.getKey());
    glLinkProgram(id);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::string infoLogStr = infoLog;
        std::cout << infoLogStr <<  std::endl;
        std::cout << tessEvalShader.getSource() <<  std::endl;


        throw new std::invalid_argument("ERROR::PROGRAM::COMPILATION_FAILED\n"
                                        + infoLogStr);
    }

    vertexShader.deleteShader();
    fragmentShader.deleteShader();
    tessControlShader.deleteShader();
    tessEvalShader.deleteShader();
}


void Program::use() const{
    glUseProgram(id);
}

GLuint Program::getID() const{
    return id;
}