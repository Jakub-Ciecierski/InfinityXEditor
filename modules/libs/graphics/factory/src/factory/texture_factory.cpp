#include "factory/texture_factory.h"

#include <shaders/textures/texture_loader.h>
#include <resources/resources.h>

namespace ifx {

using namespace std;

TextureFactory::TextureFactory() {

}

TextureFactory::~TextureFactory() {

}

Texture TextureFactory::LoadExampleCubemap() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepathBase = resources.GetResourcePath("cubemap/sor_sea/sea_",
                                                    ifx::ResourceType::TEXTURE);
    std::vector<std::string> filepathFaces = {
            filepathBase + "rt.JPG",
            filepathBase + "lf.JPG",
            filepathBase + "up.JPG",
            filepathBase + "dn.JPG",
            filepathBase + "bk.JPG",
            filepathBase + "ft.JPG"
    };
    return textureLoader.loadCubemap(filepathFaces);


/*
    string filepathBase = "res/textures/cubemap/sb_strato/stratosphere_";
    std::vector<std::string> filepathFaces = {
            filepathBase+"rt.jpg",
            filepathBase+"lf.jpg",
            filepathBase+"up.jpg",
            filepathBase+"dn.jpg",
            filepathBase+"bk.jpg",
            filepathBase+"ft.jpg"
    };
    return loadCubemap(filepathFaces);*/
/*
    string filepathBase = "res/textures/cubemap/sb_iceflow/iceflow_";
    std::vector<std::string> filepathFaces = {
            filepathBase+"rt.jpg",
            filepathBase+"lf.jpg",
            filepathBase+"up.jpg",
            filepathBase+"dn.jpg",
            filepathBase+"bk.jpg",
            filepathBase+"ft.jpg"
    };
    return loadCubemap(filepathFaces);*/
}

Texture TextureFactory::LoadDynamicBlueDiffuseTexture() {
    TextureLoader textureLoader;

    int width = 128;
    int height = 128;
    int pixel_data = 3;
    int count = width * height * pixel_data;
    int pixelCount = count / pixel_data;
    unsigned char *data = new unsigned char[count];

    int pixelIndex = 0;
    for (int i = 0; i < pixelCount; i++) {
        data[pixelIndex + 0] = 0;
        data[pixelIndex + 1] = 255;
        data[pixelIndex + 2] = 0;

        pixelIndex += pixel_data;
    }
    Texture texture = textureLoader.loadFromData(TextureTypes::DIFFUSE, data,
                                                 width, height);

    delete data;

    return texture;
}

Texture TextureFactory::LoadDynamicBlueSpecularTexture() {
    TextureLoader textureLoader;

    int width = 128;
    int height = 128;
    int pixel_data = 3;
    int count = width * height * pixel_data;
    int pixelCount = (count) / pixel_data;
    unsigned char *data = new unsigned char[count];

    int pixelIndex = 0;
    for (int i = 0; i < pixelCount; i++) {
        data[pixelIndex + 0] = 0;
        data[pixelIndex + 1] = 255;
        data[pixelIndex + 2] = 0;

        pixelIndex += pixel_data;
    }
    Texture texture = textureLoader.loadFromData(TextureTypes::SPECULAR,
                                                 data, width, height);

    delete data;

    return texture;
}

Texture TextureFactory::LoadTesselationDiffuse() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepath = resources.GetResourcePath("teselation/diffuse.jpg",
                                                ifx::ResourceType::TEXTURE);
    GLuint id = textureLoader.loadFromFile(filepath.c_str());
    Texture texture = textureLoader.contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::DIFFUSE;

    return texture;
}

Texture TextureFactory::LoadTesselationSpecular() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepath = resources.GetResourcePath("teselation/diffuse.jpg",
                                                ifx::ResourceType::TEXTURE);
    GLuint id = textureLoader.loadFromFile(filepath.c_str());

    Texture texture = textureLoader.contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::SPECULAR;

    return texture;
}

Texture TextureFactory::LoadTesselationNormals() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepath = resources.GetResourcePath("teselation/normals.jpg",
                                                ifx::ResourceType::TEXTURE);
    GLuint id = textureLoader.loadFromFile(filepath.c_str());

    Texture texture = textureLoader.contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::NORMAL;

    return texture;
}

Texture TextureFactory::LoadTesselationHeight() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepath = resources.GetResourcePath("teselation/height.jpg",
                                                ifx::ResourceType::TEXTURE);
    GLuint id = textureLoader.loadFromFile(filepath.c_str());

    Texture texture = textureLoader.contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::DISPLACEMENT;

    return texture;
}

Texture TextureFactory::LoadContainer() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepath = resources.GetResourcePath("container.png",
                                                ifx::ResourceType::TEXTURE);
    GLuint id = textureLoader.loadFromFile(filepath.c_str());

    Texture texture = textureLoader.contructTexture(id, GL_TEXTURE_2D);

    return texture;
}

Texture TextureFactory::LoadContainerDiffuse() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepath = resources.GetResourcePath("container_diff.png",
                                                ifx::ResourceType::TEXTURE);
    GLuint id = textureLoader.loadFromFile(filepath.c_str());

    Texture texture = textureLoader.contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::DIFFUSE;

    return texture;
}

Texture TextureFactory::LoadPortalTexture() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepath = resources.GetResourcePath("portal/portal_wall.jpg",
                                                ifx::ResourceType::TEXTURE);
    GLuint id = textureLoader.loadFromFile(filepath.c_str());

    Texture texture = textureLoader.contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::DIFFUSE;

    return texture;
}

Texture TextureFactory::LoadContainerSpecular() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepath = resources.GetResourcePath("container_specular.png",
                                                ifx::ResourceType::TEXTURE);
    GLuint id = textureLoader.loadFromFile(filepath.c_str());

    Texture texture = textureLoader.contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::SPECULAR;

    return texture;
}

Texture TextureFactory::LoadAwesomeFace() {
    TextureLoader textureLoader;

    ifx::Resources &resources = ifx::Resources::GetInstance();
    string filepath = resources.GetResourcePath("awesomeface.png",
                                                ifx::ResourceType::TEXTURE);
    GLuint id = textureLoader.loadFromFile(filepath.c_str());

    Texture texture = textureLoader.contructTexture(id, GL_TEXTURE_2D);

    return texture;
}
}