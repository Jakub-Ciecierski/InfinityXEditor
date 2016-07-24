#ifndef DUCK_TEXTURE_LOADER_H
#define DUCK_TEXTURE_LOADER_H

#include <model/mesh_data.h>
#include <vector>

/*
 * Class loads textures saved in resource files
 */
class TextureLoader {
private:
    GLuint loadFromFile(std::string filepath);
    Texture contructTexture(GLuint id, GLenum Type);

public:

    TextureLoader();

    ~TextureLoader();
    Texture loadFromData(TextureTypes type, unsigned char* data,
                         int width, int height);

    Texture loadTexture(std::string filepath,
                        TextureTypes type,
                        GLenum glType = GL_TEXTURE_2D);
    Texture loadCubemap(std::vector<std::string> filepath);

    Texture LoadExampleCubemap();

    Texture LoadDynamicBlueDiffuseTexture();
    Texture LoadDynamicBlueSpecularTexture();

    Texture LoadTesselationDiffuse();
    Texture LoadTesselationSpecular();
    Texture LoadTesselationNormals();
    Texture LoadTesselationHeight();

    Texture LoadContainer();
    Texture LoadContainerDiffuse();
    Texture LoadContainerSpecular();

    Texture LoadAwesomeFace();
};


#endif //DUCK_TEXTURE_LOADER_H
