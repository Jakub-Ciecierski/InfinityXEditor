#include <lighting/types/light_point.h>
#include <lighting/builders/pointlight_shader_builder.h>

namespace ifx {

LightPoint::LightPoint() : LightSource() {

}

LightPoint::LightPoint(MovableObject *renderObject) :
        LightSource(renderObject) {

}

LightPoint::~LightPoint() {

}

void LightPoint::bind(const Program &program, int id) {
    const glm::vec3 &pos = getPosition();

    ifx::PointlightShaderBuilder builder(id);
    builder.build();

    // Light Position
    GLint lightPosLoc = glGetUniformLocation(program.getID(),
                                             builder.POSITION.c_str());

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

    glUniform3f(lightPosLoc, pos.x, pos.y, pos.z);

    glUniform3f(lightAmbientLoc,
                light.ambient.x, light.ambient.y, light.ambient.z);
    glUniform3f(lightDiffuseLoc,
                light.diffuse.x, light.diffuse.y, light.diffuse.z);
    glUniform3f(lightSpecularLoc,
                light.specular.x, light.specular.y, light.specular.z);

    glUniform1f(attenConstLoc, light.constant);
    glUniform1f(attenLineLoc, light.linear);
    glUniform1f(attenQuadLoc, light.quadratic);
}
}