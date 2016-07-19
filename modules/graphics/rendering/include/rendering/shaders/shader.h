#ifndef DUCK_SHADER_H
#define DUCK_SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
private:
    GLuint id;
    std::string shaderSource;

protected:
    /*
     * Creates a shader: Vertex/Fragmet/Geometry
     */
    virtual GLuint createShader() = 0;

public:

    Shader(std::string vertexShaderSource);
    virtual ~Shader();

    /*
     * compile function has to be called before using shader
     */
    void compile();

    /*
     * Used after linking with the progam.
     */
    void deleteShader();

    GLuint getKey();

    std::string getSource();
};


#endif //DUCK_SHADER_H
