#include "shaders/buffers/fbo.h"

#include <stdexcept>

namespace ifx {

FBO::FBO(Texture texture) :
        texture_(texture){
    glGenFramebuffers(1, &id_);
}

FBO::~FBO() {
    glDeleteFramebuffers(1, &id_);
}

void FBO::compile(){
    bind();
    compileTexture();
    compileRBO();

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw new std::invalid_argument("Framebuffer is not complete!");

    unbind();
}

void FBO::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, id_);
}

void FBO::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::compileTexture(){
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D, texture_.id, 0);
}
void FBO::compileRBO(){
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
                          texture_.width, texture_.height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, rbo);
}

} // ifx