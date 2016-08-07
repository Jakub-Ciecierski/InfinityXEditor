#ifndef DUCK_TEXTURE_LOADER_H
#define DUCK_TEXTURE_LOADER_H

#include "shaders/data/shader_data.h"
#include <vector>

/*
 * Class loads textures.
 */
class TextureLoader {
public:

    TextureLoader();

    ~TextureLoader();

    Texture loadFromData(TextureTypes type, unsigned char* data,
                         int width, int height);

    Texture loadTexture(std::string filepath,
                        TextureTypes type,
                        GLenum glType = GL_TEXTURE_2D);
    Texture loadCubemap(std::vector<std::string> filepath);

    GLuint loadFromFile(std::string filepath);
    Texture contructTexture(GLuint id, GLenum Type);

};


#endif //DUCK_TEXTURE_LOADER_H
