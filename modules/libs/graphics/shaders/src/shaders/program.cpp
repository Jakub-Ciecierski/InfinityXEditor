#include "shaders/program.h"

#include <shaders/loaders/shader_loader.h>
#include <resource/resource_memory_cache.h>

#include <stdexcept>
#include <iostream>

Program::Program(Shaders shaders) :
        Resource(GetProgramPath(shaders), ResourceType::SHADER) {
    linkShaders(shaders.vertexShader, 
                shaders.fragmentShader,
                shaders.geometryShader,
                shaders.tessControlShader, 
                shaders.tessEvalShader);

    vertex_shader.reset(shaders.vertexShader);
    fragment_shader.reset(shaders.fragmentShader);
    geometry_shader.reset(shaders.geometryShader);
    tess_control_shader.reset(shaders.tessControlShader);
    tess_eval_shader.reset(shaders.tessEvalShader);
}

Program::~Program() {
    glDeleteProgram(id);
}

// static
std::shared_ptr<Program> Program::MakeProgram(Shaders& shaders){
    std::shared_ptr<Program> program
        = std::static_pointer_cast<Program>(ResourceMemoryCache::GetInstance()
            .Get(Program::GetProgramPath(shaders)));
    if(!program){
        program = std:make_shared<Program>(shaders);
    }
    ResourceMemoryCache::GetInstance().Add(program);
    
    return program;
}

void Program::linkShaders() {
    id = glCreateProgram();

    if(vertexShader)
        glAttachShader(id, vertexShader->getKey());
    if(fragmentShader)
        glAttachShader(id, fragmentShader->getKey());
    if(geometryShader)
        glAttachShader(id, geometryShader->getKey());
    if(tessControlShader)
        glAttachShader(id, tessControlShader->getKey());
    if(tessEvalShader)
        glAttachShader(id, tessEvalShader->getKey());

    glLinkProgram(id);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::string infoLogStr = infoLog;
        std::cout << infoLogStr <<  std::endl;

        throw new std::invalid_argument("ERROR::PROGRAM::COMPILATION_FAILED\n"
                                        + infoLogStr);
    }

    if(vertexShader)
        vertexShader->deleteShader();
    if(fragmentShader)
        fragmentShader->deleteShader();
    if(geometryShader)
        geometryShader->deleteShader();
    if(tessControlShader)
        tessControlShader->deleteShader();
    if(tessEvalShader)
        tessEvalShader->deleteShader();
}


void Program::use() const{
    glUseProgram(id);
}

void Program::Reload(){
    glDeleteProgram(id);

    if (vertex_shader)
        vertex_shader->Reload();
    if (fragment_shader)
        fragment_shader->Reload();
    if (geometry_shader)
        geometry_shader->Reload();
    if (tess_control_shader)
        tess_control_shader->Reload();
    if (tess_eval_shader)
        tess_eval_shader->Reload();

    linkShaders();
}

GLuint Program::getID() const{
    return id;
}

// static
std::string Program::GetProgramPath(Shaders& shaders) {
    std::string path = "";
    if(shaders.vertexShader)
        path += shaders.vertexShader->file_path();
    if(shaders.fragmentShader)
        path += shaders.fragmentShader->file_path();
    if(shaders.geometryShader)
        path += shaders.geometryShader->file_path();
    if(shaders.tessControlShader)
        path += shaders.tessControlShader->file_path();
    if(shaders.tessEvalShader)
        path += shaders.tessEvalShader->file_path();
    
    return path;
}