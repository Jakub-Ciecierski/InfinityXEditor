#include "lighting/builders/pointlight_shader_builder.h"
#include <shaders/data/shader_data.h>

using namespace ifx;

ifx::PointlightShaderBuilder::PointlightShaderBuilder(int id) :
        LightShaderBuilder(id){
}

ifx::PointlightShaderBuilder::~PointlightShaderBuilder() {

}

void ifx::PointlightShaderBuilder::build() {
    POSITION = appendToBase(id,
                            LIGHT_POINTLIGHT_NAME,
                            LIGHT_POSITION_NAME);
    DIRECTION= appendToBase(id,
                            LIGHT_POINTLIGHT_NAME,
                            LIGHT_DIRECTION_NAME);

    AMBIENT = appendToBase(id,
                           LIGHT_POINTLIGHT_NAME,
                           LIGHT_AMBIENT_NAME);
    DIFFUSE = appendToBase(id,
                           LIGHT_POINTLIGHT_NAME,
                           LIGHT_DIFFUSE_NAME);
    SPECULAR = appendToBase(id,
                            LIGHT_POINTLIGHT_NAME,
                            LIGHT_SPECULAR_NAME);

    ATTEN_CONSTANT = appendToBase(id,
                                  LIGHT_POINTLIGHT_NAME,
                                  LIGHT_ATTENUATION_CONST_NAME);
    ATTEN_LINEAR = appendToBase(id,
                                LIGHT_POINTLIGHT_NAME,
                                LIGHT_ATTENUATION_LINEAR_NAME);
    ATTEN_QUAD = appendToBase(id,
                              LIGHT_POINTLIGHT_NAME,
                              LIGHT_ATTENUATION_QUAD_NAME);
}
