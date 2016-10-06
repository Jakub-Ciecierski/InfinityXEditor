//
// Created by jakub on 5/23/16.
//

#ifndef DUCK_OBJECT_H
#define DUCK_OBJECT_H

#include "object/object_id.h"

#include <string>

class Object {
private:

    ObjectID id;

public:

    Object(ObjectID id);

    virtual ~Object();

    virtual void update() = 0;

};


#endif //DUCK_OBJECT_H
