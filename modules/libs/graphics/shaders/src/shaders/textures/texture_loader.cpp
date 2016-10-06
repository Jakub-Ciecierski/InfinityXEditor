#include <GL/glew.h>

#include "shaders/textures/texture_loader.h"

#include <SOIL.h>
#include <stdexcept>

using namespace std;

TextureLoader::TextureLoader(){}

TextureLoader::~TextureLoader() {}

Texture TextureLoader::CreateEmptyTexture(TextureTypes type,
                                          TextureInternalFormat format,
                                          TexturePixelType pixel_type,
                                          int width, int height){
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    GLenum format_gl = GetTextureInternalFormatPrimitive(format);
    glTexImage2D(GL_TEXTURE_2D, 0,
                 format_gl,
                 width, height, 0,
                 format_gl,
                 GetTexturePixelTypePrimitive(pixel_type), NULL);

    glBindTexture(GL_TEXTURE_2D, 0);

    Texture tex = contructTexture(id, GL_TEXTURE_2D);
    tex.texType = type;
    tex.width = width;
    tex.height = height;
    tex.format = format;

    return tex;
}

Texture TextureLoader::CreateEmptyTexture(TextureTypes type,
                                          int width, int height){
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 width, height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    Texture tex = contructTexture(id, GL_TEXTURE_2D);
    tex.texType = type;
    tex.width = width;
    tex.height = height;

    return tex;
}

Texture TextureLoader::loadFromData(TextureTypes type, unsigned char* data,
                                    int width, int height){
    GLuint id;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // TODO parametrize this:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    Texture tex = contructTexture(id, GL_TEXTURE_2D);
    tex.texType = type;

    return tex;
}

GLuint TextureLoader::loadFromFile(std::string filepath) {
    GLuint id;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // TODO parametrize this:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    unsigned char* image = SOIL_load_image(filepath.c_str(),
                                           &width, &height, 0,
                                           SOIL_LOAD_RGB);
    if(image == NULL){
        std::string info = "NULL returned";
        throw new std::invalid_argument(info);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);

    glBindTexture(GL_TEXTURE_2D, 0);

    return id;
}

Texture TextureLoader::contructTexture(GLuint id, GLenum type){
    return Texture(id, type);
}

Texture TextureLoader::loadTexture(std::string filepath,
                                   TextureTypes type,
                                   GLenum glType){
    GLuint id = loadFromFile(filepath);

    Texture texture = contructTexture(id, glType);
    texture.texType = type;

    return texture;
}

Texture TextureLoader::loadCubemap(vector<string> filepathFaces){
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);

    int width,height;
    unsigned char* image;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < filepathFaces.size(); i++)
    {
        image = SOIL_load_image(filepathFaces[i].c_str(),
                                &width, &height, 0, SOIL_LOAD_RGB);
        if(image == NULL){
            std::string info = "NULL returned";
            throw new std::invalid_argument(info);
        }
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
        );
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    Texture tex = contructTexture(textureID, GL_TEXTURE_CUBE_MAP);
    tex.texType = TextureTypes::CUBEMAP;
    return tex;
}