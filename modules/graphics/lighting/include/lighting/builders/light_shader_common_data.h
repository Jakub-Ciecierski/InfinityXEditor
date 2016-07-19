#ifndef DUCK_LIGHT_SHADER_COMMON_DATA_H
#define DUCK_LIGHT_SHADER_COMMON_DATA_H

#include <string>

namespace ifx {

    extern const std::string LIGHT_POINTLIGHT_COUNT;
    extern const std::string LIGHT_DIRLIGHT_COUNT;
    extern const std::string LIGHT_SPOTLIGHT_COUNT;

    extern const std::string LIGHT_SEPARATOR;
    extern const std::string LIGHT_SPOTLIGHT_NAME;
    extern const std::string LIGHT_POINTLIGHT_NAME;
    extern const std::string LIGHT_DIRLIGHT_NAME;

    extern const std::string LIGHT_POSITION_NAME;
    extern const std::string LIGHT_DIRECTION_NAME;
    extern const std::string LIGHT_AMBIENT_NAME;
    extern const std::string LIGHT_DIFFUSE_NAME;
    extern const std::string LIGHT_SPECULAR_NAME;

    extern const std::string LIGHT_ATTENUATION_CONST_NAME;
    extern const std::string LIGHT_ATTENUATION_LINEAR_NAME;
    extern const std::string LIGHT_ATTENUATION_QUAD_NAME;

    extern const std::string LIGHT_FLASHLIGHT_CUTOFF_NAME;
    extern const std::string LIGHT_FLASHLIGHT_OUTER_CUTOFF_NAME;
}

#endif //DUCK_LIGHT_SHADER_COMMON_DATA_H
