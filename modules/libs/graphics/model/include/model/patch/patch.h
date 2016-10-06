#ifndef TESELATION_PATCH_H
#define TESELATION_PATCH_H

#include <model/mesh.h>

/*
 * Patch DrawingMode is always set to GL_PATCHES
 */
class Patch : public Mesh{
private:
    float tessLevelInner;
    float tessLevelOuter;

    int vertexCountPerPatch;

    bool doDrawControlPolygon;

    int idI;
    int idJ;

    void bindTessLevel(const Program& program);
    void drawPolygon();

public:
    Patch(std::vector<Vertex> vertices,
          std::vector <GLuint>& indices,
          std::vector<Texture>& textures,
          float tessLevelInner = 3.0,
          float tessLevelOuter = 3.0,
          int vertexCountPerPatch = 4,
          int idI = 0, int idJ = 0);

    Patch(std::vector<Vertex> vertices,
          std::vector <GLuint>& indices,
          std::vector<Texture>& textures,
          Material material,
          float tessLevelInner = 3.0,
          float tessLevelOuter = 3.0,
          int vertexCountPerPatch = 4,
          int idI = 0, int idJ = 0);

    ~Patch();

    void addToTessLevelInner(float lvl);
    void addToTessLevelOuter(float lvl);

    void setTessLevelInner(float lvl);
    void setTessLevelOuter(float lvl);

    void setDrawPolygon(bool val);

    virtual void draw(const Program& program) override;
};


#endif //TESELATION_PATCH_H
