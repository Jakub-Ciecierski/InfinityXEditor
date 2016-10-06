#include <model/patch/patch.h>

#include <shaders/program.h>

Patch::Patch(std::vector<Vertex> vertices,
             std::vector <GLuint>& indices,
             std::vector<Texture>& textures,
             float tessLevelInner,
             float tessLevelOuter,
             int vertexCountPerPatch,
             int idI, int idJ) :
        Mesh(vertices, indices, textures,
             GL_LINES, GL_PATCHES),
        tessLevelInner(tessLevelInner), tessLevelOuter(tessLevelOuter),
        vertexCountPerPatch(vertexCountPerPatch),
        doDrawControlPolygon(false),
        idI(idI), idJ(idJ){

}

Patch::Patch(std::vector<Vertex> vertices,
             std::vector <GLuint>& indices,
             std::vector<Texture>& textures,
             Material material,
             float tessLevelInner,
             float tessLevelOuter,
             int vertexCountPerPatch,
             int idI, int idJ) :
        Mesh(vertices, indices, textures,
             material, GL_LINES, GL_PATCHES),
        tessLevelInner(tessLevelInner), tessLevelOuter(tessLevelOuter),
        vertexCountPerPatch(vertexCountPerPatch),
        doDrawControlPolygon(false),
        idI(idI), idJ(idJ){

}

Patch::~Patch() {

}

void Patch::bindTessLevel(const Program& program) {
    GLint tessInnerLoc
            = glGetUniformLocation(program.getID(),
                                   TESSELLATION_LVL_INNER_NAME.c_str());

    GLint tessOuterLoc
            = glGetUniformLocation(program.getID(),
                                   TESSELLATION_LVL_OUTER_NAME.c_str());

    GLint idILoc
            = glGetUniformLocation(program.getID(),
                                   PATCH_ID_I_NAME.c_str());
    GLint idJLoc
            = glGetUniformLocation(program.getID(),
                                   PATCH_ID_J_NAME.c_str());

    glUniform1f(tessInnerLoc, this->tessLevelInner);
    glUniform1f(tessOuterLoc, this->tessLevelOuter);
    glUniform1i(idILoc, this->idI);
    glUniform1i(idJLoc, this->idJ);
}

void Patch::addToTessLevelInner(float lvl){
    tessLevelInner += lvl;
    if(tessLevelInner < 1){
        tessLevelInner = 1;
    }
}

void Patch::addToTessLevelOuter(float lvl){
    tessLevelOuter += lvl;
    if(tessLevelOuter < 1){
        tessLevelOuter = 1;
    }
}

void Patch::setTessLevelInner(float lvl) {
    this->tessLevelInner = lvl;
}

void Patch::setTessLevelOuter(float lvl) {
    this->tessLevelOuter = lvl;
}

void Patch::setDrawPolygon(bool val){
    this->doDrawControlPolygon = val;
}

void Patch::draw(const Program &program) {
    bindTessLevel(program);
    // TODO should be called once
    glPatchParameteri(GL_PATCH_VERTICES, vertexCountPerPatch);

    //this->drawingMode = GL_PATCHES;

    Mesh::draw(program);
}
