#ifndef DUCK_MESH_DATA_H
#define DUCK_MESH_DATA_H

#include <math/math_ifx.h>
#include <GL/glew.h>
#include <string>
#include <vector>

/**
 * Provides all the data used by Meshes and Lights.
 * Provides uniform global strings for shader binding.
 * TODO Separate the Mesh, Light and shader data.
 */

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    glm::vec3 Tangent;
    glm::vec3 Binormal;
};

struct InstancedData {
    unsigned int data_count;
    std::vector<glm::mat4> model_matrices;
};

enum class TextureTypes{
    DIFFUSE, SPECULAR, NORMAL, DISPLACEMENT, CUBEMAP, FBO
};

enum class TextureInternalFormat{
    RGB, DEPTH_COMPONENT
};

enum class TexturePixelType{
    FLOAT, UNSIGNED_BYTE
};

GLenum GetTextureInternalFormatPrimitive(TextureInternalFormat format);
GLenum GetTexturePixelTypePrimitive(TexturePixelType type);

struct TextureParameter{
    GLenum param;
    GLenum value;
};

struct Texture{
    GLuint id;
    TextureTypes texType;
    // e.g. GL_TEXTURE_2D
    GLenum type;
    TextureInternalFormat format;

    int width;
    int height;

    std::string path; // physical path on the disk of the texture

    Texture(){}
    Texture(GLuint id,
            GLenum type) : id(id), type(type){}

    void Delete(){
        glDeleteTextures(1, &id);
    }

    void AddParameter(TextureParameter param){
        Bind();
        glTexParameteri(type, param.param, param.value);
        Unbind();
    }

    void Bind(){
        glBindTexture(type, id);
    }

    void Unbind(){
        glBindTexture(type, 0);
    }

    void updateData(unsigned char* data, int width, int height, int dim){
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

struct Material{
    float shininess;
};

struct Light{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // Attenuation
    float constant;
    float linear;
    float quadratic;

    // FlashLight cutOff angle, in degrees
    float cutOff;
    float outerCutOff;
};

// Maximum number of textures
extern const int MAX_TEX_COUNT;

/*
 * These names must correspond to texture samplers names in fragment shader
 */
extern const std::string TEX_UNI_NAMES[];

extern const std::string MODEL_MATRIX_NAME;
extern const std::string VIEW_MATRIX_NAME;
extern const std::string PROJECTION_MATRIX_NAME;

extern const std::string VIEW_POSITION_NAME;

extern const std::string MATERIAL_AMBIENT_NAME;
extern const std::string MATERIAL_DIFFUSE_NAME;
extern const std::string MATERIAL_SPECULAR_NAME;
extern const std::string MATERIAL_NORMAL_NAME;
extern const std::string MATERIAL_DISPLACEMENT_NAME;
extern const std::string MATERIAL_SHININESS_NAME;

extern const std::string TEXTURE_CUBEMAP_NAME;
// Used in FBO screen rendering
extern const std::string TEXTURE_SCREEN_NAME;

extern const std::string TEXTURE_SHADOW_MAP;

extern const std::string TESSELLATION_LVL_INNER_NAME;
extern const std::string TESSELLATION_LVL_OUTER_NAME;
extern const std::string PATCH_ID_I_NAME;
extern const std::string PATCH_ID_J_NAME;

/**
 * Light
 */
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

extern const std::string LIGHT_SPACE_MATRIX_NAME;

extern const std::string LIGHT_ATTENUATION_CONST_NAME;
extern const std::string LIGHT_ATTENUATION_LINEAR_NAME;
extern const std::string LIGHT_ATTENUATION_QUAD_NAME;

extern const std::string LIGHT_FLASHLIGHT_CUTOFF_NAME;
extern const std::string LIGHT_FLASHLIGHT_OUTER_CUTOFF_NAME;

#endif //DUCK_MESH_DATA_H
