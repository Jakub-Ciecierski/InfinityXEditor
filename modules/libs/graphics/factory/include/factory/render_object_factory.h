#ifndef PROJECT_RENDER_OBJECT_FACTORY_H
#define PROJECT_RENDER_OBJECT_FACTORY_H

#include <rendering/render_object.h>

namespace ifx {

class FBORenderer;
class Window;
class ShadowMapping;

class RenderObjectFactory {
public:

    RenderObjectFactory();

    ~RenderObjectFactory();

    FBORenderer* CreateFBORenderer(Window* window);

    ShadowMapping* CreateShadowMapping();

    RenderObject* CreateAsteroidField();
    RenderObject* CreateAsteroid();
    RenderObject* CreateNanosuitObject();

    /*
    RenderObject* loadBicubicBezierSurfaceC0Object();
    RenderObject* loadBicubicBezierPatchObject();
    RenderObject* loadBicubicBezierBowlPatchObject();
    RenderObject* loadBicubicBezierAsymmetricPatchObject();

    RenderObject* loadSquareObject();
    RenderObject* loadCubeObject();
    RenderObject* loadCubemapObject();
    RenderObject* loadLampObject();
    */
};
}

#endif //PROJECT_RENDER_OBJECT_FACTORY_H
