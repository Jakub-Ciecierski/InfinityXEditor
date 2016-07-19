#include "lighting/builders/light_shader_common_data.h"

namespace ifx {

    const std::string LIGHT_POINTLIGHT_COUNT = "pointlightCount";
    const std::string LIGHT_DIRLIGHT_COUNT = "dirlightCount";
    const std::string LIGHT_SPOTLIGHT_COUNT = "spotlightCount";

    const std::string LIGHT_SEPARATOR = ".";
    const std::string LIGHT_SPOTLIGHT_NAME = "spotLights";
    const std::string LIGHT_POINTLIGHT_NAME = "pointLights";
    const std::string LIGHT_DIRLIGHT_NAME = "dirLights";

    const std::string LIGHT_POSITION_NAME = "position";
    const std::string LIGHT_DIRECTION_NAME = "direction";

    const std::string LIGHT_AMBIENT_NAME = "ambient";
    const std::string LIGHT_DIFFUSE_NAME = "diffuse";
    const std::string LIGHT_SPECULAR_NAME = "specular";

    const std::string LIGHT_ATTENUATION_CONST_NAME = "constant";
    const std::string LIGHT_ATTENUATION_LINEAR_NAME = "linear";
    const std::string LIGHT_ATTENUATION_QUAD_NAME = "quadratic";

    const std::string LIGHT_FLASHLIGHT_CUTOFF_NAME = "cutOff";
    const std::string LIGHT_FLASHLIGHT_OUTER_CUTOFF_NAME = "outerCutOff";

}