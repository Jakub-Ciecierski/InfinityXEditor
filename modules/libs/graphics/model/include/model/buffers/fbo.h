#ifndef PROJECT_FBO_H
#define PROJECT_FBO_H

#include <GL/glew.h>
#include <shaders/data/shader_data.h>

namespace ifx {

/**
 * Frame Buffer Object. Created RenderObjectBuffer for depth and stencil.
 * Must call compile before using.
 */
class FBO {
public:

    FBO(Texture texture);

    ~FBO();

    Texture texture(){return texture_;}

    /**
     * Finishes the creation of FBO.
     * Binds the texture and completes FBO.
     * Throws exception if FBO compilation not was not complete.
     */
    void compile();

    /**
     * Binds to this FBO
     */
    void bind();

    /**
     * Unbinds from this FBO and binds back to default FBO.
     */
    void unbind();

private:
    void compileTexture();
    void compileRBO();

    GLuint id_;
    Texture texture_;
};

}

#endif //PROJECT_FBO_H
