#include "model/mesh_data.h"

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

const std::string VIEW_POSITION_NAME = "viewPos";

const std::string MATERIAL_DIFFUSE_NAME = "material.diffuse";
const std::string MATERIAL_SPECULAR_NAME = "material.specular";
const std::string MATERIAL_NORMAL_NAME = "material.normal";
const std::string MATERIAL_DISPLACEMENT_NAME = "material.displacement";
const std::string MATERIAL_SHININESS_NAME = "material.shininess";

const std::string TEXTURE_CUBEMAP_NAME = "cubemap";

const std::string TESSELLATION_LVL_INNER_NAME = "TessLevelInner";
const std::string TESSELLATION_LVL_OUTER_NAME = "TessLevelOuter";

const std::string PATCH_ID_I_NAME = "patchIDI";
const std::string PATCH_ID_J_NAME = "patchIDJ";