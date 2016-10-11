#ifndef DUCK_PROGRAM_H
#define DUCK_PROGRAM_H

#include "shaders/shaders/fragment_shader.h"
#include "shaders/shaders/vertex_shader.h"
#include "shaders/shaders/geometry_shader.h"
#include "shaders/shaders/tess_control_shader.h"
#include "shaders/shaders/tess_eval_shader.h"
#include <resources/resource.h>

#include <memory>

struct Shaders{
    VertexShader* vertexShader = nullptr;
    FragmentShader* fragmentShader = nullptr;
    GeometryShader* geometryShader = nullptr;
    TessControlShader* tessControlShader = nullptr;
    TessEvalShader* tessEvalShader = nullptr;
};

/*
 * This class encapsulates all shaders and is used to draw Meshes
 */
class Program : public ifx::Resource {
public:
    static std::shared_ptr<Program> MakeProgram(Shaders& shaders);

    ~Program();

    void use() const;
    void Reload();
    
    GLuint getID() const;

    static std::string GetProgramPath(Shaders& shaders);

private:
    Program(Shaders shaders);

    void linkShaders();

    GLuint id;

    std::unique_ptr<VertexShader> vertex_shader;
    std::unique_ptr<FragmentShader> fragment_shader;
    std::unique_ptr<GeometryShader> geometry_shader;
    std::unique_ptr<TessControlShader> tess_control_shader;
    std::unique_ptr<TessEvalShader> tess_eval_shader;
};


#endif //DUCK_PROGRAM_H
