#include <lighting/types/light_spotlight.h>
#include <lighting/builders/spotlight_shader_builder.h>

namespace ifx {

LightSpotlight::LightSpotlight() : LightDirectional() {

}

LightSpotlight::LightSpotlight(MovableObject *object) :
        LightDirectional(object) {

}

LightSpotlight::~LightSpotlight() {

}

void LightSpotlight::bind(const Program &program, int id) {
    const glm::vec3 &pos = getPosition();
    const glm::vec3 dir = getDirection();

    ifx::SpotLightShaderBuilder builder(id);
    builder.build();

    // Light Position
    GLint lightPosLoc = glGetUniformLocation(program.getID(),
                                             builder.POSITION.c_str());

    GLint lightDirLoc = glGetUniformLocation(program.getID(),
                                             builder.DIRECTION.c_str());

    GLint lightAmbientLoc = glGetUniformLocation(program.getID(),
                                                 builder.AMBIENT.c_str());
    GLint lightDiffuseLoc = glGetUniformLocation(program.getID(),
                                                 builder.DIFFUSE.c_str());
    GLint lightSpecularLoc = glGetUniformLocation(program.getID(),
                                                  builder.SPECULAR.c_str());

    GLint attenConstLoc = glGetUniformLocation(program.getID(),
                                               builder.ATTEN_CONSTANT.c_str());
    GLint attenLineLoc = glGetUniformLocation(program.getID(),
                                              builder.ATTEN_LINEAR.c_str());
    GLint attenQuadLoc = glGetUniformLocation(program.getID(),
                                              builder.ATTEN_QUAD.c_str());

    // Light Cutoff
    GLint lightCutoffLoc = glGetUniformLocation(program.getID(),
                                                builder.CUTOFF.c_str());

    GLint lightOuterCutoffLoc = glGetUniformLocation(program.getID(),
                                                     builder.OUTCUTOFF.c_str());

    glUniform3f(lightPosLoc, pos.x, pos.y, pos.z);
    glUniform3f(lightDirLoc, dir.x, dir.y, dir.z);

    glUniform3f(lightAmbientLoc,
                light.ambient.x, light.ambient.y, light.ambient.z);
    glUniform3f(lightDiffuseLoc,
                light.diffuse.x, light.diffuse.y, light.diffuse.z);
    glUniform3f(lightSpecularLoc,
                light.specular.x, light.specular.y, light.specular.z);

    glUniform1f(attenConstLoc, light.constant);
    glUniform1f(attenLineLoc, light.linear);
    glUniform1f(attenQuadLoc, light.quadratic);

    glUniform1f(lightOuterCutoffLoc, glm::cos(glm::radians(light.outerCutOff)));
    glUniform1f(lightCutoffLoc, glm::cos(glm::radians(light.cutOff)));
}
}