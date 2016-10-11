#ifndef PROJECT_TEXTURE_FACTORY_H
#define PROJECT_TEXTURE_FACTORY_H

#include "shaders/data/shader_data.h"

namespace ifx {

class TextureFactory {
private:

public:

    TextureFactory();

    ~TextureFactory();

    Texture LoadExampleCubemap();

    Texture LoadDynamicBlueDiffuseTexture();

    Texture LoadDynamicBlueSpecularTexture();

    Texture LoadTesselationDiffuse();

    Texture LoadTesselationSpecular();

    Texture LoadTesselationNormals();

    Texture LoadTesselationHeight();

    Texture LoadContainer();
    Texture LoadPortalTexture();
    Texture LoadContainerDiffuse();

    Texture LoadContainerSpecular();

    Texture LoadAwesomeFace();

};
} // ifx

#endif //PROJECT_TEXTURE_FACTORY_H
