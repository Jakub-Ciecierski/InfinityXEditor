#include "rendering/shadows/shadow_mapping.h"

#include <lighting/types/light_directional.h>
#include <shaders/buffers/fbo.h>
#include <shaders/textures/texture_loader.h>
#include <rendering/scene/scene.h>
#include <shaders/program.h>

namespace ifx {

ShadowMapping::ShadowMapping(Dimensions dimensions,
                             std::shared_ptr<Program> program) :
        program_(program),
        dimensions_(dimensions){
    InitFBO(CreateTexture());
}

ShadowMapping::~ShadowMapping(){

}

void ShadowMapping::Render(Scene* scene){
    glViewport(0, 0, dimensions_.width, dimensions_.height);

    const std::vector<LightDirectional *>& lights
            = scene->light_group()->light_directions();
    for(unsigned int i = 0; i < lights.size(); i++){
        program_->use();
        BindLightMatrix(program_.get(), lights[i]);

        fbo_->bind();
        glClear(GL_DEPTH_BUFFER_BIT);
        scene->render(program_.get());
        fbo_->unbind();
    }

    glActiveTexture(GL_TEXTURE0);
    fbo_->texture().Bind();
    glUniform1i(glGetUniformLocation(program_->getID(),
                                     TEXTURE_SHADOW_MAP.c_str()), 0);
}

Texture ShadowMapping::CreateTexture(){
    Texture texture = TextureLoader().CreateEmptyTexture(
            TextureTypes::FBO,
            TextureInternalFormat::DEPTH_COMPONENT,
            TexturePixelType::FLOAT,
            dimensions_.width, dimensions_.height);
    texture.AddParameter(TextureParameter{GL_TEXTURE_MIN_FILTER, GL_NEAREST});
    texture.AddParameter(TextureParameter{GL_TEXTURE_MAG_FILTER, GL_NEAREST});
    texture.AddParameter(TextureParameter{GL_TEXTURE_WRAP_S, GL_REPEAT});
    texture.AddParameter(TextureParameter{GL_TEXTURE_WRAP_T, GL_REPEAT});

    return texture;
}

void ShadowMapping::InitFBO(Texture texture){
    fbo_.reset(new FBO(texture, FBOType::DEPTH));
    fbo_->compile();
}

void ShadowMapping::BindLightMatrix(const Program* program,
                                    LightDirectional* light){
    GLint lightSpaceMatrixLoc
            = glGetUniformLocation(program->getID(),
                                   LIGHT_SPACE_MATRIX_NAME.c_str());
    glm::mat4 mat = light->GetLightSpaceMatrix();
    glUniformMatrix4fv(lightSpaceMatrixLoc, 1, GL_FALSE,
                       glm::value_ptr(light->GetLightSpaceMatrix()));

}

} // ifx

