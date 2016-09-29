#include <shaders/data/shader_data.h>

GLenum GetTextureInternalFormatPrimitive(TextureInternalFormat format){
    if(format == TextureInternalFormat::RGB)
        return GL_RGB;
    else if(format == TextureInternalFormat::DEPTH_COMPONENT)
        return GL_DEPTH_COMPONENT;
}

GLenum GetTexturePixelTypePrimitive(TexturePixelType type){
    if(type == TexturePixelType::FLOAT)
        return GL_FLOAT;
    else if(type == TexturePixelType::UNSIGNED_BYTE)
        return GL_UNSIGNED_BYTE;
}


// Maximum number of textures
const int MAX_TEX_COUNT = 16;

/*
 * This names must correspond to texture samplers names in fragment shader
 */
const std::string TEX_UNI_NAMES[MAX_TEX_COUNT] = {
        "tex1", "tex2", "tex3", "tex4",
        "tex5", "tex6", "tex7", "tex8",
        "tex9", "tex10", "tex11", "tex12",
        "tex13", "tex14", "tex15", "tex16",
};

const std::string MODEL_MATRIX_NAME = "ModelMatrix";
const std::string VIEW_MATRIX_NAME = "ViewMatrix";
const std::string PROJECTION_MATRIX_NAME = "ProjectionMatrix";

const std::string LIGHT_SPACE_MATRIX_NAME = "LightSpaceMatrix";

const std::string VIEW_POSITION_NAME = "viewPos";

const std::string MATERIAL_DIFFUSE_NAME = "material.diffuse";
const std::string MATERIAL_SPECULAR_NAME = "material.specular";
const std::string MATERIAL_NORMAL_NAME = "material.normal";
const std::string MATERIAL_DISPLACEMENT_NAME = "material.displacement";
const std::string MATERIAL_SHININESS_NAME = "material.shininess";

const std::string TEXTURE_CUBEMAP_NAME = "cubemap";
const std::string TEXTURE_SCREEN_NAME = "screen_texture";

const std::string TEXTURE_SHADOW_MAP = "shadow_map";

const std::string TESSELLATION_LVL_INNER_NAME = "TessLevelInner";
const std::string TESSELLATION_LVL_OUTER_NAME = "TessLevelOuter";

const std::string PATCH_ID_I_NAME = "patchIDI";
const std::string PATCH_ID_J_NAME = "patchIDJ";

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