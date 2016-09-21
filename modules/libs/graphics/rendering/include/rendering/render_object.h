#ifndef DUCK_RENDER_OBJECT_H
#define DUCK_RENDER_OBJECT_H

#include <object/movable_object.h>
#include <model/mesh.h>
#include <model/model.h>

#include <math/math_ifx.h>
#include <shaders/program.h>

/*
 * RenderObject is used to render Meshes.
 * Takes ownership over program.
 */
class RenderObject : public ifx::MovableObject {
public:
    RenderObject(ObjectID id,
                 Model* model);

    virtual ~RenderObject();

    const std::vector<Program*>& programs(){return programs_;}

    Model* getModel();

    void addProgram(Program* program);

    /*
     * Binds the Model matrix and draws Mesh
     */
    virtual void render(const Program& program);
protected:
    Model* model;

private:

    std::vector<Program*> programs_;

};


#endif //DUCK_RENDER_OBJECT_H
