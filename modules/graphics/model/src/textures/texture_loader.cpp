//
// Created by jakub on 5/25/16.
//

#include <SOIL.h>
#include <GL/glew.h>
#include <stdexcept>
#include "texture_loader.h"

using namespace std;

TextureLoader::TextureLoader(){

}

TextureLoader::~TextureLoader() {

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

Texture TextureLoader::LoadExampleCubemap(){

    string filepathBase = "res/textures/cubemap/sor_sea/sea_";
    std::vector<std::string> filepathFaces = {
            filepathBase+"rt.JPG",
            filepathBase+"lf.JPG",
            filepathBase+"up.JPG",
            filepathBase+"dn.JPG",
            filepathBase+"bk.JPG",
            filepathBase+"ft.JPG"
    };
    return loadCubemap(filepathFaces);


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

Texture TextureLoader::LoadDynamicBlueDiffuseTexture() {
    int width = 128;
    int height = 128;
    int pixel_data = 3;
    int count = width * height * pixel_data;
    int pixelCount = count / pixel_data;
    unsigned char* data = new unsigned char[count];

    int pixelIndex = 0;
    for(int i = 0; i < pixelCount; i++){
        data[pixelIndex + 0] = 0;
        data[pixelIndex + 1] = 255;
        data[pixelIndex + 2] = 0;

        pixelIndex += pixel_data;
    }
    Texture texture = loadFromData(TextureTypes::DIFFUSE, data, width, height);

    delete data;

    return texture;
}

Texture TextureLoader::LoadDynamicBlueSpecularTexture() {
    int width = 128;
    int height = 128;
    int pixel_data = 3;
    int count = width * height * pixel_data;
    int pixelCount = (count) / pixel_data;
    unsigned char* data = new unsigned char[count];

    int pixelIndex = 0;
    for(int i = 0; i < pixelCount; i++){
        data[pixelIndex + 0] = 0;
        data[pixelIndex + 1] = 255;
        data[pixelIndex + 2] = 0;

        pixelIndex += pixel_data;
    }
    Texture texture = loadFromData(TextureTypes::SPECULAR, data, width, height);

    delete data;

    return texture;
}

Texture TextureLoader::LoadTesselationDiffuse() {
    GLuint id = loadFromFile("res/textures/teselation/diffuse.jpg");
    Texture texture = contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::DIFFUSE;

    return texture;
}

Texture TextureLoader::LoadTesselationSpecular() {
    GLuint id = loadFromFile("res/textures/teselation/diffuse.jpg");
    Texture texture = contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::SPECULAR;

    return texture;
}

Texture TextureLoader::LoadTesselationNormals() {
    GLuint id = loadFromFile("res/textures/teselation/normals.jpg");
    Texture texture = contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::NORMAL;

    return texture;
}

Texture TextureLoader::LoadTesselationHeight() {
    GLuint id = loadFromFile("res/textures/teselation/height.jpg");
    Texture texture = contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::DISPLACEMENT;

    return texture;
}

Texture TextureLoader::LoadContainer() {
    GLuint id = loadFromFile("res/textures/container.jpg");
    Texture texture = contructTexture(id, GL_TEXTURE_2D);

    return texture;
}

Texture TextureLoader::LoadContainerDiffuse(){
    GLuint id = loadFromFile("res/textures/container_diff.png");
    Texture texture = contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::DIFFUSE;

    return texture;
}

Texture TextureLoader::LoadContainerSpecular(){
    GLuint id = loadFromFile("res/textures/container_specular.png");
    Texture texture = contructTexture(id, GL_TEXTURE_2D);
    texture.texType = TextureTypes::SPECULAR;

    return texture;
}

Texture TextureLoader::LoadAwesomeFace() {
    GLuint id = loadFromFile("res/textures/awesomeface.png");
    Texture texture = contructTexture(id, GL_TEXTURE_2D);

    return texture;
}
