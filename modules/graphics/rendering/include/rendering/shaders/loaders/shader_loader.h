#ifndef DUCK_SHADER_LOADER_H
#define DUCK_SHADER_LOADER_H

#include <rendering/shaders/shader.h>
#include <rendering/shaders/fragment_shader.h>
#include <rendering/shaders/vertex_shader.h>
#include <rendering/shaders/tess_control_shader.h>
#include <rendering/shaders/tess_eval_shader.h>

/*
 * Logic behind loading Shaders from files
 */
class ShaderLoader {
private:

    std::string getShaderCode(const GLchar* path);
public:

    ShaderLoader();

    ~ShaderLoader();

    VertexShader loadVertexShader(const GLchar* path);
    FragmentShader loadFragmentShader(const GLchar* path);
    TessControlShader loadTessControlShader(const GLchar *path);
    TessEvalShader loadTessEvalShader(const GLchar *path);

    static VertexShader LoadDefaultVertexShader();
    static FragmentShader LoadDefaultFragmentShader();
};


#endif //DUCK_SHADER_LOADER_H
