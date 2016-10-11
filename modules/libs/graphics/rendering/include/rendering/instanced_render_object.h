#ifndef PROJECT_INSTANCED_RENDERER_H
#define PROJECT_INSTANCED_RENDERER_H

#include <object/render_object.h>

#include <memory>

namespace ifx {

/**
 * Collection of MovableObjects which are rendered together with the same model
 * and shaders using the technique of instanced array rendering.
 *
 * TODO InstancedRenderer should not be a MovableObject.
 */
class InstancedRenderObject : public RenderObject {
public:
    InstancedRenderObject(ObjectID id, std::shared_ptr<Model> model,
                          InstancedData& instanced_data);

    ~InstancedRenderObject();

    // Overridden from RenderObject
    void render(const Program& program) override;

private:
    InstancedData instanced_data_;
};
}

#endif //PROJECT_INSTANCED_RENDERER_H
