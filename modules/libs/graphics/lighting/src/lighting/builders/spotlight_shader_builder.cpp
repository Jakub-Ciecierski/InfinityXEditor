#include "lighting/builders/spotlight_shader_builder.h"
#include <shaders/data/shader_data.h>

using namespace std;
using namespace ifx;

SpotLightShaderBuilder::SpotLightShaderBuilder(int id) :
        LightShaderBuilder(id){

}

void SpotLightShaderBuilder::build() {
    POSITION = appendToBase(id,
                            LIGHT_SPOTLIGHT_NAME,
                            LIGHT_POSITION_NAME);
    DIRECTION = appendToBase(id, LIGHT_SPOTLIGHT_NAME,
                             LIGHT_DIRECTION_NAME);

    CUTOFF = appendToBase(id, LIGHT_SPOTLIGHT_NAME,
                          LIGHT_FLASHLIGHT_CUTOFF_NAME);
    OUTCUTOFF = appendToBase(id, LIGHT_SPOTLIGHT_NAME,
                             LIGHT_FLASHLIGHT_OUTER_CUTOFF_NAME);

    AMBIENT = appendToBase(id, LIGHT_SPOTLIGHT_NAME,
                           LIGHT_AMBIENT_NAME);
    DIFFUSE = appendToBase(id, LIGHT_SPOTLIGHT_NAME,
                           LIGHT_DIFFUSE_NAME);
    SPECULAR = appendToBase(id, LIGHT_SPOTLIGHT_NAME,
                            LIGHT_SPECULAR_NAME);

    ATTEN_CONSTANT = appendToBase(id, LIGHT_SPOTLIGHT_NAME,
                                  LIGHT_ATTENUATION_CONST_NAME);
    ATTEN_LINEAR = appendToBase(id,LIGHT_SPOTLIGHT_NAME,
                                LIGHT_ATTENUATION_LINEAR_NAME);
    ATTEN_QUAD = appendToBase(id,LIGHT_SPOTLIGHT_NAME,
                              LIGHT_ATTENUATION_QUAD_NAME);
}