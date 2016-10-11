#include "object/render_object.h"

using namespace glm;

RenderObject::RenderObject(ObjectID id,
                           std::shared_ptr<Model> model) :
        ifx::MovableObject(id), model(model) {}

RenderObject::~RenderObject(){}

void RenderObject::addProgram(std::shared_ptr<Program> program){
    programs_.push_back(program);
}

void RenderObject::render(const Program& program){
    program.use();

    // Model
    GLint transformLoc = glGetUniformLocation(program.getID(),
                                              MODEL_MATRIX_NAME.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

    model->draw(program);
}