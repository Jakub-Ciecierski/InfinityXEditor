#ifndef DUCK_RENDER_OBJECT_H
#define DUCK_RENDER_OBJECT_H

#include <object/object.h>
#include <model/mesh.h>
#include <model/model.h>

#include <glm/gtc/matrix_transform.hpp>

enum RenderModels{
    MAIN_MODEL, SUB_MODEL
};

/*
 * RenderObject is used to render Meshes.
 */
class RenderObject : public Object{
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scaleFactor;

    glm::mat4 ModelMatrix;

    Model* model;

    void initVectors();
public:
    RenderObject(ObjectID id, std::string name,
                 Model* model);

    ~RenderObject();

    /*
     * Moves to position
     */
    void moveTo(const glm::vec3& position);

    /*
     * Moves by the position vector.
     * The position is added to current on
     */
    void move(const glm::vec3& position);

    /*
     * Rotates to given rotation vector
     */
    void rotateTo(const glm::vec3& rotate);

    /*
     * Rotates by the rotation vector.
     * The values are added to current one
     */
    void rotate(const glm::vec3& rotate);

    void scale(const glm::vec3& scale);

    const glm::vec3& getPosition();

    Model* getModel();

    /*
     * Binds the Model matrix and draws Mesh
     */
    void render(const Program& program,
                RenderModels renderModel = RenderModels::MAIN_MODEL);

    /*
     * Updates the Model Matrix
     */
    void update();
};


#endif //DUCK_RENDER_OBJECT_H
