#include "lighting/builders/dirlight_shader_builder.h"
#include <shaders/data/shader_data.h>

using namespace ifx;

ifx::DirlightShaderBuilder::DirlightShaderBuilder(int id) :
        LightShaderBuilder(id){

}

ifx::DirlightShaderBuilder::~DirlightShaderBuilder() {

}

void ifx::DirlightShaderBuilder::build() {
    DIRECTION= appendToBase(id,
                            LIGHT_DIRLIGHT_NAME,
                            LIGHT_DIRECTION_NAME);

    AMBIENT = appendToBase(id,
                           LIGHT_DIRLIGHT_NAME,
                           LIGHT_AMBIENT_NAME);
    DIFFUSE = appendToBase(id,
                           LIGHT_DIRLIGHT_NAME,
                           LIGHT_DIFFUSE_NAME);
    SPECULAR = appendToBase(id,
                            LIGHT_DIRLIGHT_NAME,
                            LIGHT_SPECULAR_NAME);

    LIGHT_SPACE_MATRIX = appendToBase(id,
                                      LIGHT_DIRLIGHT_NAME,
                                      LIGHT_SPACE_MATRIX_NAME);
}
