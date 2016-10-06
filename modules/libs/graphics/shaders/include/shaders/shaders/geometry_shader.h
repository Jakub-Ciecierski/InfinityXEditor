#ifndef PROJECT_GEOMETRY_SHADER_H
#define PROJECT_GEOMETRY_SHADER_H

#include "shaders/shader.h"

class GeometryShader : public Shader{
public:

    GeometryShader(std::string shaderSource,
                   std::string file_path);
    GeometryShader(const GeometryShader& other);

    ~GeometryShader();

protected:
    virtual GLuint createShader() override;

};


#endif //PROJECT_GEOMETRY_SHADER_H