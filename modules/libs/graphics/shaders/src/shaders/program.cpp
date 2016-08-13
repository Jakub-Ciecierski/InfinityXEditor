#include "shaders/program.h"

#include <stdexcept>
#include <iostream>
#include <shaders/loaders/shader_loader.h>

Program::Program(){

}

Program::Program(VertexShader* vertexShader,
                 FragmentShader* fragmentShader,
                 TessControlShader* tessControlShader,
                 TessEvalShader* tessEvalShader){
    linkShaders(vertexShader, fragmentShader,
                tessControlShader, tessEvalShader);

    if(vertexShader != nullptr)
        programs.vertex_shader = new VertexShader(*vertexShader);
    else
        programs.vertex_shader = nullptr;

    if(fragmentShader != nullptr)
        programs.fragment_shader = new FragmentShader(*fragmentShader);
    else
        programs.fragment_shader = nullptr;

    if(tessControlShader != nullptr)
        programs.tess_control_shader = new TessControlShader(*tessControlShader);
    else
        programs.tess_control_shader = nullptr;

    if(tessEvalShader != nullptr)
        programs.tess_eval_shader = new TessEvalShader(*tessEvalShader);
    else
        programs.tess_eval_shader = nullptr;
}

Program::~Program() {
    glDeleteProgram(id);

    delete programs.vertex_shader;
    delete programs.fragment_shader;
    delete programs.tess_control_shader;
    delete programs.tess_eval_shader;
}

void Program::linkShaders(VertexShader* vertexShader,
                          FragmentShader* fragmentShader,
                          TessControlShader* tessControlShader,
                          TessEvalShader* tessEvalShader) {
    id = glCreateProgram();

    if(vertexShader != nullptr)
        glAttachShader(id, vertexShader->getKey());
    if(fragmentShader != nullptr)
        glAttachShader(id, fragmentShader->getKey());
    if(tessControlShader != nullptr)
        glAttachShader(id, tessControlShader->getKey());
    if(tessEvalShader != nullptr)
        glAttachShader(id, tessEvalShader->getKey());

    glLinkProgram(id);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::string infoLogStr = infoLog;
        std::cout << infoLogStr <<  std::endl;
        std::cout << tessEvalShader->getSource() <<  std::endl;

        throw new std::invalid_argument("ERROR::PROGRAM::COMPILATION_FAILED\n"
                                        + infoLogStr);
    }

    if(vertexShader != nullptr)
        vertexShader->deleteShader();
    if(fragmentShader != nullptr)
        fragmentShader->deleteShader();
    if(tessControlShader != nullptr)
        tessControlShader->deleteShader();
    if(tessEvalShader != nullptr)
        tessEvalShader->deleteShader();
}


void Program::use() const{
    glUseProgram(id);
}

void Program::Reload(){
    glDeleteProgram(id);

    if (programs.vertex_shader != nullptr)
        programs.vertex_shader->Reload();
    if (programs.fragment_shader != nullptr)
        programs.fragment_shader->Reload();
    if (programs.tess_control_shader != nullptr)
        programs.tess_control_shader->Reload();
    if (programs.tess_eval_shader != nullptr)
        programs.tess_eval_shader->Reload();

    linkShaders(programs.vertex_shader,
                programs.fragment_shader,
                programs.tess_control_shader,
                programs.tess_eval_shader);
}

GLuint Program::getID() const{
    return id;
}