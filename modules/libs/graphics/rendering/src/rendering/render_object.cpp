#include "rendering/render_object.h"

using namespace glm;

RenderObject::RenderObject(ObjectID id,
                           Model* model) :
        ifx::MovableObject(id), model(model) {

}

RenderObject::~RenderObject(){
    for(unsigned int i = 0; i < programs_.size(); i++){
        if(programs_[i] != nullptr)
            delete programs_[i];
    }
}

void RenderObject::addProgram(Program* program){
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