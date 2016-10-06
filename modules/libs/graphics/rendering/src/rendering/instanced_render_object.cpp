#include "rendering/instanced_render_object.h"

namespace ifx {

InstancedRenderObject::InstancedRenderObject(ObjectID id,
                                             std::shared_ptr<Model> model,
                                             InstancedData& instanced_data) :
    RenderObject(id, model),
    instanced_data_(instanced_data) {
    const std::vector<Mesh*>& meshes = model->getMeshes();
    for(unsigned int i = 0; i < meshes.size(); i++){
        VAO* vao = meshes[i]->vao();
        vao->bindInstancedRenderingBuffers(instanced_data);
    }
}

InstancedRenderObject::~InstancedRenderObject(){}

void InstancedRenderObject::render(const Program& program){
    program.use();

    model->drawInstanced(program, instanced_data_.data_count);
}

} // namespace ifx