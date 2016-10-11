#include "shaders/program.h"

#include <shaders/loaders/shader_loader.h>
#include <resources/resource_memory_cache.h>

#include <stdexcept>
#include <iostream>

Program::Program(Shaders shaders) :
        Resource(GetProgramPath(shaders), ifx::ResourceType::SHADER) {
    vertex_shader.reset(shaders.vertexShader);
    fragment_shader.reset(shaders.fragmentShader);
    geometry_shader.reset(shaders.geometryShader);
    tess_control_shader.reset(shaders.tessControlShader);
    tess_eval_shader.reset(shaders.tessEvalShader);

    linkShaders();
}

Program::~Program() {
    glDeleteProgram(id);
}

// static
std::shared_ptr<Program> Program::MakeProgram(Shaders& shaders){
    std::shared_ptr<Program> program
        = std::static_pointer_cast<Program>(ifx::ResourceMemoryCache::GetInstance()
            .Get(Program::GetProgramPath(shaders)));
    if(!program){
        program = std::shared_ptr<Program>(new Program(shaders));
    }
    ifx::ResourceMemoryCache::GetInstance().Add(program);
    
    return program;
}

void Program::linkShaders() {
    id = glCreateProgram();

    if(vertex_shader)
        glAttachShader(id, vertex_shader->getKey());
    if(fragment_shader)
        glAttachShader(id, fragment_shader->getKey());
    if(geometry_shader)
        glAttachShader(id, geometry_shader->getKey());
    if(tess_control_shader)
        glAttachShader(id, tess_control_shader->getKey());
    if(tess_eval_shader)
        glAttachShader(id, tess_eval_shader->getKey());

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

    if(vertex_shader)
        vertex_shader->deleteShader();
    if(fragment_shader)
        fragment_shader->deleteShader();
    if(geometry_shader)
        geometry_shader->deleteShader();
    if(tess_control_shader)
        tess_control_shader->deleteShader();
    if(tess_eval_shader)
        tess_eval_shader->deleteShader();
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