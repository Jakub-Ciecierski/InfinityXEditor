#include "shaders/buffers/fbo.h"

#include <stdexcept>

namespace ifx {

FBO::FBO(Texture texture, FBOType type) :
        texture_(texture),
        type_(type),
        compiled_(false){
    glGenFramebuffers(1, &id_);
}

FBO::~FBO() {
    glDeleteFramebuffers(1, &id_);
}

void FBO::compile(){
    if(compiled_)
        return;

    bind();

    if(type_ == FBOType::COLOR_DEPTH)
        compileColorDepth();
    else if(type_ == FBOType::DEPTH)
        compileDepth();

    CheckError();
    unbind();

    compiled_ = true;
}

void FBO::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, id_);
}

void FBO::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::compileColorDepth(){
    compileTexture(GL_COLOR_ATTACHMENT0);
    compileRBO();
}

void FBO::compileDepth(){
    compileTexture(GL_DEPTH_ATTACHMENT);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
}

void FBO::compileTexture(GLenum attachment){
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           attachment,
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

void FBO::CheckError(){
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw new std::invalid_argument("Framebuffer is not complete!");
}

} // ifx