#ifndef DUCK_PROGRAM_H
#define DUCK_PROGRAM_H

#include "shaders/shaders/fragment_shader.h"
#include "shaders/shaders/vertex_shader.h"
#include "shaders/shaders/tess_control_shader.h"
#include "shaders/shaders/tess_eval_shader.h"

/*
 * This class encapsulates all shaders and is used to draw Meshes
 */
class Program {
public:

    Program();
    Program(VertexShader* vertexShader = nullptr,
            FragmentShader* fragmentShader = nullptr,
            TessControlShader* tessControlShader = nullptr,
            TessEvalShader* tessEvalShader = nullptr);

    ~Program();

    void use() const;

    void Reload();

    GLuint getID() const;

private:
    void linkShaders(VertexShader* vertexShader,
                     FragmentShader* fragmentShader,
                     TessControlShader* tessControlShader,
                     TessEvalShader* tessEvalShader);

    GLuint id;

    struct Programs{
        VertexShader* vertex_shader;
        FragmentShader* fragment_shader;
        TessControlShader* tess_control_shader;
        TessEvalShader* tess_eval_shader;
    };
    Programs programs;
};


#endif //DUCK_PROGRAM_H
