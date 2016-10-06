//
// Created by jakub on 5/24/16.
//

#include "object/object_id.h"

ObjectID::ObjectID(int key) : key(key){

}

ObjectID::~ObjectID() {

}

bool ObjectID::operator==(const ObjectID &id) const {
    return id.key == this->key;
}

bool ObjectID::operator!=(const ObjectID &id) const {
    return id.key != this->key;
}