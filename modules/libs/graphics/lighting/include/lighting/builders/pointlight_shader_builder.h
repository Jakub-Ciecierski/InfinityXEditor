#ifndef DUCK_POINTLIGHT_SHADER_BUILDER_H
#define DUCK_POINTLIGHT_SHADER_BUILDER_H

#include "lighting/builders/light_shader_builder.h"

namespace ifx {

    class PointlightShaderBuilder : public LightShaderBuilder{

    public:
        std::string POSITION;
        std::string DIRECTION;

        std::string AMBIENT;
        std::string DIFFUSE;
        std::string SPECULAR;

        std::string ATTEN_CONSTANT;
        std::string ATTEN_LINEAR;
        std::string ATTEN_QUAD;

        PointlightShaderBuilder(int id);

        ~PointlightShaderBuilder();

        virtual void build() override;
    };
}

#endif //DUCK_POINTLIGHT_SHADER_BUILDER_H
