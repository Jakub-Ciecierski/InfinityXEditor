#ifndef DUCK_OBJECT_ID_H
#define DUCK_OBJECT_ID_H

class ObjectID {
private:
    int key;

public:

    ObjectID(int key);

    ~ObjectID();

    bool operator==(const ObjectID& id) const;
    bool operator!=(const ObjectID &id) const;
};


#endif //DUCK_OBJECT_ID_H
