#include "rendering/render_object.h"

using namespace glm;

RenderObject::RenderObject(ObjectID id, std::string name,
                           Model* model) :
        ifx::MovableObject(id, name), model(model){

}

RenderObject::~RenderObject(){

}

void RenderObject::render(const Program& program,
                          RenderModels renderModel){
    program.use();

    // Model
    GLint transformLoc = glGetUniformLocation(program.getID(),
                                              MODEL_MATRIX_NAME.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

    if(renderModel == RenderModels::MAIN_MODEL){
        model->draw(program);
    }
    else if(renderModel == RenderModels::SUB_MODEL){
        model->drawSubMeshes(program);
    }
}

void RenderObject::update(){
    ModelMatrix = mat4(1.0f);

    glm::mat4 Translate = translate(glm::mat4(1.0f), position);

    glm::mat4 RotateX
            = glm::rotate(glm::mat4(1.0f),
                          glm::radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 RotateY
            = glm::rotate(glm::mat4(1.0f),
                          glm::radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 RotateZ
            = glm::rotate(glm::mat4(1.0f),
                          glm::radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 Scale = glm::scale(glm::mat4(1.0f), scaleFactor);

    glm::mat4 Rotate =  RotateZ * RotateY * RotateX;

    ModelMatrix = Translate * Rotate * Scale;
}

Model *RenderObject::getModel() {
    return model;
}
