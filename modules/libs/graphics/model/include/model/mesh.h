#ifndef DUCK_MESH_H
#define DUCK_MESH_H

#include "shaders/program.h"
#include "shaders/data/shader_data.h"

#include "shaders/buffers/vbo.h"
#include "shaders/buffers/vao.h"

#include <GL/glew.h>
#include <memory>
#include <vector>

#include <iostream>

/*
 * Contains the geometry of an object.
 * Vertices, indices, textures and material is defined.
 *
 * One instance of the same Mesh should be present in the system.
 * Use Multiple RenderObjects to bind the same Mesh
 */
class Mesh {
public:
    Mesh();
    Mesh(std::vector<Vertex> vertices,
         std::vector <GLuint>& indices,
         GLenum drawingMode = GL_TRIANGLES,
         GLenum polygonMode = GL_FILL);

    Mesh(std::vector<Vertex> vertices,
         std::vector <GLuint>& indices,
         std::vector<Texture>& textures,
         GLenum drawingMode = GL_TRIANGLES,
         GLenum polygonMode = GL_FILL);

    Mesh(std::vector<Vertex> vertices,
         std::vector <GLuint>& indices,
         std::vector<Texture>& textures,
         Material material,
         GLenum drawingMode  = GL_TRIANGLES,
         GLenum polygonMode = GL_FILL);

    Mesh(const Mesh& mesh) = delete;
    Mesh& operator=(const Mesh& other) = delete;

    virtual ~Mesh();

    VAO* vao() {return vao_.get();};
    VBO* vbo() {return vbo_.get();};

    void setPolygonMode(GLenum polygonMode);
    void setPrimitiveMode(GLenum drawingMode);
    void setMaterial(const Material& material);
    void addTexture(Texture texture);

    std::vector<Texture*> getTextures(TextureTypes type);

    virtual void draw(const Program& program);
    virtual void drawInstanced(const Program& program, int count);

    std::string toString() const;

protected:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    GLenum primitive_mode_;
    GLenum polygonMode;

    Material material;

    std::unique_ptr<VAO> vao_;
    std::unique_ptr<VBO> vbo_;
    std::unique_ptr<EBO> ebo_;

    /*
     * Checks for errors in the Mesh class and throws exceptions;
     */
    void checkError();

    /*
     * Computes the Tanget Basis for all faces
     */
    void computeTangetBasis();

    /*
     * Computes Tanget Basis for the face represented by the vertices
     */
    void computeAndStoreTangetBasis(Vertex& v1, Vertex& v2, Vertex& v3);

    void initBuffers();

    /*
     * Binds all textures during draw operation
     */
    void bindTextures(const Program& program);
    void bindColor(const Program& program);
};

#endif //DUCK_MESH_H
