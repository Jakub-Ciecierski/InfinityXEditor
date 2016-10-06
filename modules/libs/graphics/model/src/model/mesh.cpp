#include "model/mesh.h"

#include <stdexcept>

using namespace std;

Mesh::Mesh(){

}

Mesh::Mesh(std::vector<Vertex> vertices,
           vector <GLuint>& indices,
           GLenum drawingMode, GLenum polygonMode) :
        vertices(vertices), indices(indices){
    this->primitive_mode_ = drawingMode;
    this->polygonMode = polygonMode;
    checkError();

    computeTangetBasis();
    initBuffers();
}

Mesh::Mesh(std::vector<Vertex> vertices,
           vector <GLuint>& indices,
           vector<Texture>& textures,
           GLenum drawingMode, GLenum polygonMode) :
        vertices(vertices), indices(indices), textures(textures){
    this->primitive_mode_ = drawingMode;
    this->polygonMode = polygonMode;
    checkError();

    computeTangetBasis();
    initBuffers();
}

Mesh::Mesh(std::vector<Vertex> vertices,
           vector <GLuint>& indices,
           vector<Texture>& textures,
           Material material,
           GLenum drawingMode, GLenum polygonMode) :
        vertices(vertices), indices(indices), textures(textures),
        material(material){
    this->primitive_mode_ = drawingMode;
    this->polygonMode = polygonMode;

    checkError();

    computeTangetBasis();
    initBuffers();
}

Mesh::~Mesh() {
    for(auto& texture : textures){
        texture.Delete();
    }
}

void Mesh::computeTangetBasis(){
    const int DATA_PER_FACE = 3;
    int faceCount = indices.size() / DATA_PER_FACE;
    int vertexIndex = 0;


    for(int i = 0; i < faceCount; i++){
        if(vertexIndex >= indices.size()){
            throw new std::invalid_argument("computeTangetBasis out of bounds");
        }
        computeAndStoreTangetBasis(vertices[indices[vertexIndex+0]],
                                   vertices[indices[vertexIndex+1]],
                                   vertices[indices[vertexIndex+2]]);
/*
        std::cout << "Face[" << i << "]" << std::endl;
        std::cout << "V0: " << vertexIndex+0 << std::endl;
        std::cout << "V1: " << vertexIndex+1 << std::endl;
        std::cout << "V2: " << vertexIndex+2 << std::endl << std::endl;*/
        vertexIndex += DATA_PER_FACE;

    }
}
/*
void Mesh::computeAndStoreTangetBasis(Vertex& v0, Vertex& v1, Vertex& v2){
    glm::vec3 P = v1.Position - v0.Position;
    glm::vec3 Q = v2.Position - v0.Position;

    float s1 = v1.TexCoords.x - v0.TexCoords.x;
    float t1 = v1.TexCoords.y - v0.TexCoords.y;

    float s2 = v2.TexCoords.x - v0.TexCoords.x;
    float t2 = v2.TexCoords.x - v0.TexCoords.x;

    float tmp = 1.0f;
    float diff = s1*t2 - s2*t1;
    float errTol = 0.0001;
    if(fabsf(diff) >= errTol){
        tmp = 1.0f / diff;
    }
    tmp = 1.0f / diff;
    glm::vec3 tanget = glm::vec3(t2*P.x - t1*Q.x,
                                 t2*P.y - t1*Q.y,
                                 t2*P.z - t1*Q.z);
    tanget *= tmp;

    glm::vec3 binormal = glm::vec3(s1*Q.x - s2*P.x,
                                   s1*Q.y - s2*P.y,
                                   s1*Q.z - s2*P.z);
    binormal *= tmp;

    tanget = glm::normalize(tanget);
    binormal = glm::normalize(binormal);

    glm::vec3 tmpVec = P - Q;
    v0.Tangent = glm::cross(P, v0.Normal);
    v1.Tangent = glm::cross(P, v0.Normal);
    v2.Tangent = glm::cross(P, v0.Normal);

    glm::vec3 test(1.0f, 0.0f, 0.0f);
    glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f),
                                         glm::radians(90.0f),
                                         glm::vec3(0.0f, 1.0f, 0.0f));
    test = glm::vec3(rotateMatrix * glm::vec4(test, 1.0f));
    std::cout << test.x << ", " << test.y << ", " << test.z << std::endl;

    v0.Binormal = binormal;
    v1.Binormal = binormal;
    v2.Binormal = binormal;

}
*/

void Mesh::computeAndStoreTangetBasis(Vertex& v0, Vertex& v1, Vertex& v2){

    glm::vec2 & uv0 = v0.TexCoords;
    glm::vec2 & uv1 = v1.TexCoords;
    glm::vec2 & uv2 = v2.TexCoords;

    glm::vec3 deltaPos1 = v1.Position - v0.Position;
    glm::vec3 deltaPos2 = v2.Position - v0.Position;

    glm::vec2 deltaUV1 = uv1-uv0;
    glm::vec2 deltaUV2 = uv2-uv0;

    float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
    glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
    glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

    tangent = glm::normalize(tangent);
    bitangent = glm::normalize(bitangent);

    v0.Tangent = tangent;
    v1.Tangent = tangent;
    v2.Tangent = tangent;

    v0.Binormal = bitangent;
    v1.Binormal = bitangent;
    v2.Binormal = bitangent;

}

void Mesh::checkError(){
    int textureCount = textures.size();

    if(textureCount > MAX_TEX_COUNT){
        throw std::invalid_argument("Too many textures");
    }
}

void Mesh::initBuffers(){
    vao_.reset(new VAO());

    vbo_.reset(new VBO(&vertices));
    ebo_.reset(new EBO(&indices));

    vao_->bindVertexBuffers(*vbo_, *ebo_);
}

void Mesh::bindTextures(const Program& program){
    for(unsigned int j = 0; j < textures.size(); j++){
        int i = j + 31;
        glActiveTexture(GL_TEXTURE31 + j);
        textures[j].Bind();
        if(textures[j].texType == TextureTypes::DIFFUSE){
            glUniform1i(glGetUniformLocation(program.getID(),
                                             MATERIAL_DIFFUSE_NAME.c_str()),i);
        }else if(textures[j].texType == TextureTypes::SPECULAR){
            glUniform1i(glGetUniformLocation(program.getID(),
                                             MATERIAL_SPECULAR_NAME.c_str()),i);
        }else if(textures[j].texType == TextureTypes::NORMAL){
            glUniform1i(glGetUniformLocation(program.getID(),
                                             MATERIAL_NORMAL_NAME.c_str()),i);
        }else if(textures[j].texType == TextureTypes::DISPLACEMENT){
            glUniform1i(glGetUniformLocation(program.getID(),
                                             MATERIAL_DISPLACEMENT_NAME.c_str()),i);
        }else if(textures[j].texType == TextureTypes::CUBEMAP){
            glUniform1i(glGetUniformLocation(program.getID(),
                                             TEXTURE_CUBEMAP_NAME.c_str()),i);
        }else if(textures[j].texType == TextureTypes::FBO){
            glUniform1i(glGetUniformLocation(program.getID(),
                                             TEXTURE_SCREEN_NAME.c_str()),i);
        }else{
            // TODO check proper naming convetion
            glUniform1i(glGetUniformLocation(program.getID(),
                                             TEX_UNI_NAMES[i].c_str()), i);
        }
    }
}

void Mesh::bindColor(const Program& program){
    GLint matShineLoc = glGetUniformLocation(program.getID(),
                                             MATERIAL_SHININESS_NAME.c_str());
    glUniform1f(matShineLoc, material.shininess);
}

void Mesh::setPolygonMode(GLenum polygonMode){
    this->polygonMode = polygonMode;
}

void Mesh::setPrimitiveMode(GLenum drawingMode){
    this->primitive_mode_ = drawingMode;
}

void Mesh::setMaterial(const Material& material){
    this->material = material;
}

void Mesh::addTexture(Texture texture){
    this->textures.push_back(texture);
}

std::vector<Texture*> Mesh::getTextures(TextureTypes type){
    std::vector<Texture*> texturesType;
    for(unsigned int i = 0; i < textures.size(); i++){
        if(textures[i].texType == type) {
            texturesType.push_back(&textures[i]);
        }
    }
    return texturesType;
}

void Mesh::draw(const Program& program){
    program.use();

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    this->bindTextures(program);
    this->bindColor(program);

    vao_->bind();

    glDrawElements(primitive_mode_, indices.size(), GL_UNSIGNED_INT, 0);

    vao_->unbind();
}

void Mesh::drawInstanced(const Program& program, int count){
    program.use();

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    this->bindTextures(program);
    this->bindColor(program);

    vao_->bind();

    glDrawElementsInstanced(primitive_mode_, indices.size(),
                            GL_UNSIGNED_INT, 0, count);

    vao_->unbind();
}

std::string Mesh::toString() const{
    string str = "";
    int diffuseTexCount = 0;
    int specularTexCount = 0;
    int normalTexCount = 0;
    for(unsigned int i = 0; i < textures.size(); i++){
        if(textures[i].texType == TextureTypes::DIFFUSE)
            diffuseTexCount++;
        if(textures[i].texType == TextureTypes::SPECULAR)
            specularTexCount++;
        if(textures[i].texType == TextureTypes::NORMAL)
            normalTexCount++;
    }

    str += "Vertices Count:          " + to_string(vertices.size()) + "\n";
    str += "Texture Diffuse Count:   " + to_string(diffuseTexCount) + "\n";
    str += "Texture Specular Count:  " + to_string(specularTexCount) + "\n";
    str += "Texture Normal Count:  " + to_string(normalTexCount) + "\n";

    return str;
}
