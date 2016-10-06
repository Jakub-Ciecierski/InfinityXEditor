#ifndef DUCK_SHADER_H
#define DUCK_SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
public:

    Shader(std::string vertexShaderSource,
           std::string file_path);
    Shader(const Shader& other);

    virtual ~Shader();

    std::string file_path() const {return file_path_;}

    /*
     * compile function has to be called before using shader
     */
    void compile();

    /*
     * Used after linking with the progam.
     */
    void deleteShader();

    void Reload();

    GLuint getKey();

    std::string getSource();
protected:
    /*
     * Creates a shader: Vertex/Fragmet/Geometry
     */
    virtual GLuint createShader() = 0;

private:
    GLuint id;
    std::string shaderSource;
    std::string file_path_;
};


#endif //DUCK_SHADER_H
