#ifndef PROJECT_MOVABLE_OBJECT_H
#define PROJECT_MOVABLE_OBJECT_H

#include <object/object.h>
#include <math/math_ifx.h>

namespace ifx {

/**
 * TODO MovableObject should not be an object.
 */
class MovableObject : public Object {
public:

    MovableObject(ObjectID id);

    ~MovableObject();

    // Overridden from Object
    virtual void update() override;

    /*
     * Moves to position
     */
    void moveTo(const glm::vec3 &position);

    /*
     * Moves by the position vector.
     * The position is added to current on
     */
    void move(const glm::vec3 &position);

    /*
     * Rotates to given rotation vector
     */
    virtual void rotateTo(const glm::vec3 &rotate);

    /*
     * Rotates by the rotation vector.
     * The values are added to current one
     */
    virtual void rotate(const glm::vec3 &rotate);

    void scale(const glm::vec3 &scale);

    const glm::vec3& getPosition();
    const glm::vec3& getDirection();

protected:
    void initVectors();

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scaleFactor;

    glm::vec3 direction;

    glm::mat4 ModelMatrix;

private:

};
}

#endif //PROJECT_MOVABLE_OBJECT_H
