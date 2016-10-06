#ifndef PROJECT_RESOURCE_H
#define PROJECT_RESOURCE_H

#include <string>

#include <resources/resources.h>

namespace ifx {

// Used if resource was created dynamically.
extern const std::string NO_FILEPATH;

class Resource {
public:
    Resource(std::string filepath, ResourceType type);
    virtual ~Resource();

    Resource(const Resource& resource) = delete;
    Resource& operator=(const Resource& resource) = delete;

    std::string filepath(){return filepath_;};
    ResourceType type(){return type_;};

private:
    std::string filepath_;
    ResourceType type_;
};

}

#endif //PROJECT_RESOURCE_H
