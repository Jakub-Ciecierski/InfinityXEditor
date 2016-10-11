#ifndef DUCK_RENDER_OBJECT_H
#define DUCK_RENDER_OBJECT_H

#include <model/mesh.h>
#include <model/model.h>
#include <math/math_ifx.h>
#include <shaders/program.h>
#include <object/movable_object.h>

#include <memory>

/*
 * RenderObject is used to render Meshes.
 */
class RenderObject : public ifx::MovableObject {
public:
    RenderObject(ObjectID id,
                 std::shared_ptr<Model>);
    virtual ~RenderObject();

    const std::vector<std::shared_ptr<Program>>& programs(){ return programs_;}

    void SetBeforeRender(std::function<void()> before_render);
    void SetAfterRender(std::function<void()> after_render);

    Model* getModel();
    void addProgram(std::shared_ptr<Program> program);

    /*
     * Binds the Model matrix and draws Mesh
     */
    virtual void render(const Program& program);

protected:
    std::shared_ptr<Model> model;

private:

    std::vector<std::shared_ptr<Program>> programs_;

    std::function<void()> before_render_;
    std::function<void()> after_render_;

};


#endif //DUCK_RENDER_OBJECT_H
