#include "factory/mesh_factory.h"

#include "factory/texture_factory.h"
#include <shaders/textures/texture_loader.h>
#include <model/patch/patch.h>

#include <vector>

namespace ifx {

using namespace std;
using namespace glm;

MeshFactory::MeshFactory(){}

MeshFactory::~MeshFactory(){}

std::unique_ptr<Mesh> MeshFactory::LoadBicubicBezierPatch(float startX,
                                                          float startY,
                                                          float depth,
                                                          int idI, int idJ) {
    //float dx = 2.0f * 0.3333333f;
    double dx = 2.0f * 0.33333333f;
    float texDx = 0.3333333;

    vector <Vertex> vertices;
    // ROW 1
    vertices.push_back(Vertex{vec3(startX, startY, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(0.0f, 3.0f * texDx)});

    vertices.push_back(Vertex{vec3(startX + dx, startY, 0.5f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(texDx, 3.0f * texDx)});

    vertices.push_back(Vertex{vec3(startX + (2.0f * dx), startY, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(2.0f * texDx, 3.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + (2.0f), startY, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(3.0f * texDx, 3.0f * texDx)});

    // ROW 2
    vertices.push_back(Vertex{vec3(startX, startY - dx, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(0.0f, 2.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + dx, startY - dx, depth),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(texDx, 2.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + (2.0f * dx), startY - dx, depth),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(2.0f * texDx, 2.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + (2.0), startY - dx, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(3.0f * texDx, 2.0f * texDx)});

    // ROW 3
    vertices.push_back(Vertex{vec3(startX, startY - (2 * dx), 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(0.0f, 1.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + dx, startY - (2 * dx), depth),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(texDx, 1.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + (2.0f * dx),
                                   startY - (2 * dx), depth),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(2.0f * texDx, 1.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + (2.0), startY - (2 * dx), 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(3.0f * texDx, 1.0f * texDx)});

    // ROW 4
    vertices.push_back(Vertex{vec3(startX, startY - (2.0), 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(0.0f, 0.0f)});

    vertices.push_back(Vertex{vec3(startX + dx, startY - (2.0), 0.5f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(texDx, 0.0f)});

    vertices.push_back(Vertex{vec3(startX + (2.0f * dx), startY - (2.0), 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(2.0f * texDx, 0.0f)});
    vertices.push_back(Vertex{vec3(startX + (2.0), startY - (2.0), 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(3.0f * texDx, 0.0f)});

    // Indices for Patch
    vector <GLuint> indices = {
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11,
            12, 13, 14, 15
    };

    TextureFactory textureLoader;

    Texture textureDiffuse = textureLoader.LoadTesselationDiffuse();
    Texture textureSpecular = textureLoader.LoadTesselationSpecular();
    Texture textureHeight = textureLoader.LoadTesselationHeight();
    Texture textureNormal = textureLoader.LoadTesselationNormals();

    std::vector <Texture> textures = {textureDiffuse, textureSpecular,
                                      textureHeight, textureNormal};
/*
    std::unique_ptr<Mesh> mesh(new Patch(vertices, indices, textures,
                                         2.0f, 2.0f, vertices.size(), idI, idJ));
*/
    auto mesh = std::unique_ptr<Mesh>(new Patch(vertices, indices, textures,
                                               2.0f, 2.0f, vertices.size(),
                                                idI, idJ));

    mesh->setPolygonMode(GL_LINE);
    mesh->setPrimitiveMode(GL_PATCHES);

    Material material;
    material.shininess = 32.0f;

    mesh->setMaterial(material);

    return mesh;
}

std::unique_ptr<Mesh> MeshFactory::LoadBicubicBezierPolygon(float startX,
                                                            float startY,
                                           float depth, int idI, int idJ) {
    //float dx = 2.0f * 0.3333333f;
    double dx = 2.0f * 0.33333333f;
    float texDx = 0.3333333;

    vector <Vertex> vertices;
    // ROW 1
    vertices.push_back(Vertex{vec3(startX, startY, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(0.0f, 3.0f * texDx)});

    vertices.push_back(Vertex{vec3(startX + dx, startY, 0.5f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(texDx, 3.0f * texDx)});

    vertices.push_back(Vertex{vec3(startX + (2.0f * dx), startY, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(2.0f * texDx, 3.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + (2.0f), startY, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(3.0f * texDx, 3.0f * texDx)});

    // ROW 2
    vertices.push_back(Vertex{vec3(startX, startY - dx, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(0.0f, 2.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + dx, startY - dx, depth),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(texDx, 2.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + (2.0f * dx), startY - dx, depth),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(2.0f * texDx, 2.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + (2.0), startY - dx, 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(3.0f * texDx, 2.0f * texDx)});

    // ROW 3
    vertices.push_back(Vertex{vec3(startX, startY - (2 * dx), 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(0.0f, 1.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + dx, startY - (2 * dx), depth),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(texDx, 1.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + (2.0f * dx),
                                   startY - (2 * dx), depth),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(2.0f * texDx, 1.0f * texDx)});
    vertices.push_back(Vertex{vec3(startX + (2.0), startY - (2 * dx), 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(3.0f * texDx, 1.0f * texDx)});

    // ROW 4
    vertices.push_back(Vertex{vec3(startX, startY - (2.0), 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(0.0f, 0.0f)});

    vertices.push_back(Vertex{vec3(startX + dx, startY - (2.0), 0.5f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(texDx, 0.0f)});

    vertices.push_back(Vertex{vec3(startX + (2.0f * dx), startY - (2.0), 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(2.0f * texDx, 0.0f)});
    vertices.push_back(Vertex{vec3(startX + (2.0), startY - (2.0), 0.0f),
                              vec3(0.0f, 0.0f, -1.0f),
                              vec2(3.0f * texDx, 0.0f)});

    // Indices for Patch
    vector <GLuint> indices = {
            0, 1,
            1, 2,
            2, 3,

            4, 5,
            5, 6,
            6, 7,

            8, 9,
            9, 10,
            10, 11,

            12, 13,
            13, 14,
            14, 15,

            0, 4,
            4, 8,
            8, 12,

            1, 5,
            5, 9,
            9, 13,

            2, 6,
            6, 10,
            10, 14,

            3, 7,
            7, 11,
            11, 15
    };
    TextureFactory textureLoader;

    Texture textureDiffuse = textureLoader.LoadTesselationDiffuse();
    Texture textureSpecular = textureLoader.LoadTesselationSpecular();
    Texture textureHeight = textureLoader.LoadTesselationHeight();
    Texture textureNormal = textureLoader.LoadTesselationNormals();

    std::vector <Texture> textures = {textureDiffuse, textureSpecular,
                                      textureHeight, textureNormal};



    auto mesh = std::unique_ptr<Mesh>(new Patch(vertices, indices, textures,
                                                2.0f, 2.0f,
                                                vertices.size(), idI, idJ));

    mesh->setPolygonMode(GL_FILL);
    mesh->setPrimitiveMode(GL_LINES);

    Material material;
    material.shininess = 32.0f;

    mesh->setMaterial(material);

    return mesh;
}

std::unique_ptr<Mesh> MeshFactory::LoadBicubicBezierAsymmetricPatch() {
    float end = -1.0f;
    float start = 1.0f;
    float mid1 = -0.33f;
    float mid2 = 0.33f;

    float depth = 0.0f;
    float depth1 = -1.0f;
    float depth2 = 1.0f;

    vector <Vertex> vertices = {
            // Row1
            Vertex{vec3(end, start, depth1),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            Vertex{vec3(mid1, start, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},

            Vertex{vec3(mid2, start, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},

            Vertex{vec3(start, start, depth2),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},

            // Row 2
            Vertex{vec3(end, mid2, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            Vertex{vec3(mid1, mid2, depth),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},

            Vertex{vec3(mid2, mid2, depth),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},

            Vertex{vec3(start, mid2, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},

            // Row 3
            Vertex{vec3(end, mid1, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            Vertex{vec3(mid1, mid1, depth),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},

            Vertex{vec3(mid2, mid1, depth),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},

            Vertex{vec3(start, mid1, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},

            // Row 4
            Vertex{vec3(end, end, depth2),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            Vertex{vec3(mid1, end, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},

            Vertex{vec3(mid2, end, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},

            Vertex{vec3(start, end, depth1),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)}
    };

    // Indices for Patch
    vector <GLuint> indices = {
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11,
            12, 13, 14, 15
    };

    TextureFactory textureLoader;
    Texture textureDiffuse = textureLoader.LoadDynamicBlueDiffuseTexture();
    Texture textureSpecular = textureLoader.LoadDynamicBlueSpecularTexture();

    std::vector <Texture> textures = {textureDiffuse, textureSpecular};

    std::unique_ptr<Mesh> mesh(new Patch(vertices, indices, textures,
                           2.0f, 2.0f, vertices.size()));
    mesh->setPolygonMode(GL_LINE);
    mesh->setPrimitiveMode(GL_PATCHES);

    Material material;
    material.shininess = 332.0f;

    mesh->setMaterial(material);

    return mesh;
}

std::unique_ptr<Mesh> MeshFactory::LoadPatch() {
    // Position, Normal, TexCoord
    vector <Vertex> vertices = {
            // Front

            Vertex{vec3(0.0f, 1.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            Vertex{vec3(1.0f, 1.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},

            Vertex{vec3(1.0f, 0.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},

            Vertex{vec3(0.0f, 0.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)}
    };

    // Indices for Patch
    vector <GLuint> indices = {
            0, 1, 2, 3
    };

    TextureFactory textureLoader;
    Texture textureDiffuse = textureLoader.LoadDynamicBlueDiffuseTexture();
    Texture textureSpecular = textureLoader.LoadDynamicBlueSpecularTexture();

    std::vector <Texture> textures = {textureDiffuse, textureSpecular};

    std::unique_ptr<Mesh> mesh(new Patch(vertices, indices, textures));
    mesh->setPolygonMode(GL_LINE);
    mesh->setPrimitiveMode(GL_PATCHES);

    Material material;
    material.shininess = 32.0f;
    mesh->setMaterial(material);

    return mesh;
}

std::unique_ptr<Mesh> MeshFactory::LoadCubemap() {
    // Position, Normal, TexCoord
    vector <Vertex> vertices = {
            // Front
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            // Back
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},

            // Left
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Right
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Bottom
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Top
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
    };

    vector <GLuint> indices = {
            3, 1, 0, 3, 2, 1,            // front
            4, 5, 7, 5, 6, 7,            // back

            8, 9, 11, 9, 10, 11,           // left
            15, 13, 12, 15, 14, 13,        // right

            16, 17, 19, 17, 18, 19,        // bottom
            23, 21, 20, 23, 22, 21,        // top
    };
    TextureFactory textureLoader;
    Texture textureDiffuse = textureLoader.LoadExampleCubemap();

    std::vector <Texture> textures = {textureDiffuse};

    std::unique_ptr<Mesh> mesh(new Mesh(vertices, indices, textures));

    Material material;
    material.shininess = 32.0f;
    mesh->setMaterial(material);

    return mesh;
}

std::unique_ptr<Mesh> MeshFactory::LoadCube() {
    // Position, Normal, TexCoord
    vector <Vertex> vertices = {
            // Front
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            // Back
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},

            // Left
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Right
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Bottom
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Top
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
    };

    vector <GLuint> indices = {
            3, 1, 0, 3, 2, 1,            // front
            4, 5, 7, 5, 6, 7,            // back

            8, 9, 11, 9, 10, 11,           // left
            15, 13, 12, 15, 14, 13,        // right

            16, 17, 19, 17, 18, 19,        // bottom
            23, 21, 20, 23, 22, 21,        // top
    };
    TextureFactory textureLoader;
    Texture textureDiffuse = textureLoader.LoadContainerDiffuse();
    Texture textureSpecular = textureLoader.LoadContainerSpecular();

    std::vector <Texture> textures = {textureDiffuse, textureSpecular};

    std::unique_ptr<Mesh> mesh(new Mesh(vertices, indices, textures,
                                        GL_TRIANGLES));

    Material material;
    material.shininess = 32.0f;
    mesh->setMaterial(material);

    return mesh;
}

std::unique_ptr<Mesh> MeshFactory::LoadRoom() {
    vector <Vertex> vertices = {
            // Front
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            // Back
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},

            // Left
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Right
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Bottom
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Top
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
    };

    vector <GLuint> indices = {
            3, 1, 0, 3, 2, 1,            // front
            4, 5, 7, 5, 6, 7,            // back

            8, 9, 11, 9, 10, 11,           // left
            15, 13, 12, 15, 14, 13,        // right

            16, 17, 19, 17, 18, 19,        // bottom
            23, 21, 20, 23, 22, 21,        // top
    };
    TextureFactory textureLoader;
    Texture textureDiffuse = textureLoader.LoadPortalTexture();
    Texture textureSpecular = textureLoader.LoadPortalTexture();

    std::vector <Texture> textures = {textureDiffuse, textureSpecular};

    std::unique_ptr<Mesh> mesh(new Mesh(vertices, indices, textures,
                                        GL_TRIANGLES));

    Material material;
    material.shininess = 32.0f;
    mesh->setMaterial(material);

    return mesh;
}

std::unique_ptr<Mesh> MeshFactory::LoadFloor(){
    // Position, Normal, TexCoord
    vector <Vertex> vertices = {
            // Front
            Vertex{vec3(1.0f, 1.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 0.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(0.0f, 0.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(0.0f, 1.0f, 0.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},
    };

    vector <GLuint> indices = {
            0, 1, 3, 1, 2, 3,            // front
    };
    TextureFactory textureLoader;
    Texture textureDiffuse = textureLoader.LoadContainerDiffuse();
    Texture textureSpecular = textureLoader.LoadContainerSpecular();

    std::vector <Texture> textures = {textureDiffuse, textureSpecular};

    std::unique_ptr<Mesh> mesh(new Mesh(vertices, indices, textures,
                                          GL_TRIANGLES));

    Material material;
    material.shininess = 32.0f;
    mesh->setMaterial(material);

    return mesh;
}

std::unique_ptr<Mesh> MeshFactory::LoadLamp() {
    vector <Vertex> vertices = {
            // Front
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)},

            // Back
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},

            // Left
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Right
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Bottom
            Vertex{vec3(1.0f, -1.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, -1.0f, -1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, -1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, -1.0f, 1.0f),
                   vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f)},

            // Top
            Vertex{vec3(1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
            Vertex{vec3(1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, -1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},
            Vertex{vec3(-1.0f, 1.0f, 1.0f),
                   vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
    };

    vector <GLuint> indices = {
            3, 1, 0, 3, 2, 1,            // front
            4, 5, 7, 5, 6, 7,            // back

            8, 9, 11, 9, 10, 11,           // left
            15, 13, 12, 15, 14, 13,        // right

            16, 17, 19, 17, 18, 19,        // bottom
            23, 21, 20, 23, 22, 21,        // top
    };
    TextureFactory textureLoader;

    std::vector <Texture> textures;
    std::unique_ptr<Mesh> mesh(new Mesh(
            vertices, indices, textures, GL_TRIANGLES));
    return mesh;
}
} // ifx