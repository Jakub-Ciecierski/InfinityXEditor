#ifndef DUCK_LIGHT_SOURCE_H
#define DUCK_LIGHT_SOURCE_H

#include <lighting/builders/light_shader_common_data.h>
#include <rendering/render_object.h>
#include <controls/camera.h>

/*
 * Light source. Can be rendered if mesh was provided.
 * Light source can be bound if RenderObject and thus follow its position.
 *
 * Each light has its Attenuation values stored in Light struct.
 * The attenuation can be omitted by the shader itself.
 */
class LightSource {
protected:
    Light light;
    glm::vec3 position;

    RenderObject *followedRenderObject;
    Camera* followedCamera;

    // If true the position will be taken from renderObject if possible.
    bool isFollow;

    /*
     * Derived classes should implement special binding mechanism.
     * Such as binding direction for directional light.
     */
    virtual void bind(const Program& program, int id = -1) = 0;

public:

    LightSource();
    LightSource(RenderObject *renderObject);

    virtual ~LightSource();

    /*
     * Will start following input object.
     * Will set NULL to the camera
     */
    void setRenderObject(RenderObject* object);
    /*
     * Will start following the input camera.
     * Will set NULL to the  current following object
     */
    void setCamera(Camera* camera);

    /*
     * Following can set to false, if done so, the Light will not
     * follow and instead use its own position.
     */
    void setFollow(bool value);

    void setPosition(const glm::vec3& position);
    void setLight(const Light& light);

    const glm::vec3& getPosition();

    /*
     * The id is used to separated lights of the same type in the shaders.
     */
    void use(const Program& program, int id = -1);
    void render(const Program& program);
};


#endif //DUCK_LIGHT_SOURCE_H
