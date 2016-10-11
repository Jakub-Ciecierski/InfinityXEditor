#include "model_loader/model_loader.h"

#include <shaders/textures/texture_loader.h>

#include <stdexcept>
#include <iostream>

using namespace std;

ModelLoader::ModelLoader(std::string filepath) :
        filepath(filepath){

}

ModelLoader::~ModelLoader() {

}

void ModelLoader::checkError(const aiScene* scene,
                             string errorString){
    if(!scene
       || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        string info = "ERROR::ASSIMP::" + errorString;
        cout << info << endl;
        throw new std::invalid_argument(info);
    }
}

std::shared_ptr<Model> ModelLoader::loadModel() {
    Assimp::Importer importer;
    const aiScene* scene =
            importer.ReadFile(filepath,
                              aiProcess_Triangulate | aiProcess_FlipUVs);

    checkError(scene, string(importer.GetErrorString()));

    // Retrieve the directory path of the filepath
    this->directory = filepath.substr(0, filepath.find_last_of('/'));

    std::vector<std::unique_ptr<Mesh>> meshes;
    processNode(scene->mRootNode, scene, meshes);

    auto model = Model::MakeModel(filepath, std::move(meshes));
    printInfo(*model);

    return model;
}

void ModelLoader::processNode(aiNode* node, const aiScene* scene,
                              vector<std::unique_ptr<Mesh>>& meshes){
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        std::unique_ptr<Mesh> ifxMesh(this->processMesh(mesh, scene));

        // TODO Find better solution for shininess !
        Material material;
        material.shininess = 322.0f;
        ifxMesh->setMaterial(material);

        meshes.push_back(std::move(ifxMesh));
    }
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, meshes);
    }
}

Mesh* ModelLoader::processMesh(aiMesh* mesh, const aiScene* scene){
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    vertices    = processVertices(mesh);
    indices     = processIndices(mesh);
    textures    = processTextures(mesh, scene);

    return new Mesh(vertices, indices, textures);
}

vector<Vertex> ModelLoader::processVertices(aiMesh *mesh){
    vector<Vertex> vertices;
    for(GLuint i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;

        glm::vec3 vPos;
        vPos.x = mesh->mVertices[i].x;
        vPos.y = mesh->mVertices[i].y;
        vPos.z = mesh->mVertices[i].z;
        vertex.Position = vPos;

        glm::vec3 vNorm;
        if(mesh->mNormals != nullptr){
            std::cout << "No normals" << std::endl;
            vNorm.x = mesh->mNormals[i].x;
            vNorm.y = mesh->mNormals[i].y;
            vNorm.z = mesh->mNormals[i].z;
        }
        vertex.Normal = vNorm;

        // Assimp has up to 8 different textureCoords, we only care about one
        if(mesh->mTextureCoords[0]) {
            glm::vec2 vTex;
            vTex.x = mesh->mTextureCoords[0][i].x;
            vTex.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vTex;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    return vertices;
}

vector<GLuint> ModelLoader::processIndices(aiMesh *mesh){
    vector<GLuint> indices;

    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return indices;
}

vector<Texture> ModelLoader::processTextures(aiMesh* mesh,
                                             const aiScene* scene){
    vector<Texture> textures;
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps
                = loadMaterialTextures(material, aiTextureType_DIFFUSE,
                                       TextureTypes::DIFFUSE);
        vector<Texture> specularMaps
                = loadMaterialTextures(material, aiTextureType_SPECULAR,
                                       TextureTypes::SPECULAR);
        // WARNING aiTextureType_HEIGHT hide the Normal maps !!
        vector<Texture> normalMaps
                = loadMaterialTextures(material, aiTextureType_HEIGHT,
                                       TextureTypes::NORMAL);
        /*
        // Or maybe not !
        normalMaps
                = loadMaterialTextures(material, aiTextureType_NORMALS,
                                       TextureTypes::NORMAL);
                                       */
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    }
    return textures;
}

vector<Texture> ModelLoader::loadMaterialTextures(aiMaterial* mat,
                                                  aiTextureType type,
                                                  TextureTypes texType) {
    TextureLoader textureLoader;

    vector<Texture> textures;
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        string filename = string(str.C_Str());
/*
        // <Eagle HASK> :(
        string filenameTMP = string(str.C_Str());
        string filename = "";
        for(int i = 4; i < filenameTMP.size(); i++){
            if(filenameTMP[i] == '\\')
                filename += "/";
            else
                filename += filenameTMP[i];
        }
        // </Eagle HASK> :(
*/
        GLboolean skip = false;
        for(GLuint j = 0; j < textureCache.size(); j++) {
            if(textureCache[j].path == filename)
            {
                textures.push_back(textureCache[j]);
                skip = true;
                break;
            }
        }
        if(!skip) {
            std::string filepath = directory + '/' + filename;
            Texture texture = textureLoader.loadTexture(filepath,
                                                        texType);

            texture.path = string(str.C_Str());
            textures.push_back(texture);
            this->textureCache.push_back(texture);
        }
    }
    return textures;
}

void ModelLoader::printInfo(const Model& model){
    std::cout << model.toString() << std::endl;
}