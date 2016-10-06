#include "resources/resources.h"
#include "resources/resource.h"

namespace ifx {

const std::string NO_FILEPATH = "NO_FILEPATH";

Resource::Resource(std::string filepath, ResourceType type) : 
    filepath_(filepath), type_(type) {}

Resource::~Resource(){}

}