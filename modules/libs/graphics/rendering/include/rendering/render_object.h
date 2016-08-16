#ifndef DUCK_RENDER_OBJECT_H
#define DUCK_RENDER_OBJECT_H

#include <object/movable_object.h>
#include <model/mesh.h>
#include <model/model.h>

#include <math/math_ifx.h>
#include <shaders/program.h>

enum RenderModels{
    MAIN_MODEL, SUB_MODEL
};

/*
 * RenderObject is used to render Meshes.
 * Takes ownership over program.
 */
class RenderObject : public ifx::MovableObject{
private:
    glm::mat4 ModelMatrix;

    Model* model;

    std::vector<Program*> programs_;

public:
    RenderObject(ObjectID id, std::string name,
                 Model* model);

    ~RenderObject();

    const std::vector<Program*>& programs(){return programs_;}

    Model* getModel();

    void addProgram(Program* program);

    /*
     * Binds the Model matrix and draws Mesh
     */
    void render(const Program& program,
                RenderModels renderModel = RenderModels::MAIN_MODEL);

    /*
     * Override from Object
     */
    virtual void update() override;
};


#endif //DUCK_RENDER_OBJECT_H
