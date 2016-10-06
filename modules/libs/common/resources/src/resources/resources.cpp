#include "resources/resources.h"

namespace ifx {

Resources::Resources(){
    InitResourcePath();
}

void Resources::InitResourcePath(){
    resource_root_path_ = std::getenv("IFX_ROOT");
    resource_root_path_ += "/res";
}

std::string Resources::ResouceTypePath(ResourceType type){
    switch(type){
        case ResourceType::MODEL:
            return "models";
        case ResourceType::SHADER:
            return "shaders";
        case ResourceType::TEXTURE:
            return "textures";
    }
}

std::string Resources::ConcatenatePath(std::string path1, std::string path2){
    return path1 + "/" + path2;
}

Resources::~Resources(){

}

Resources& Resources::GetInstance(){
    static Resources resources;

    return resources;
}

std::string Resources::GetResourcePath(std::string name, ResourceType type){
    std::string resource_type_path = ResouceTypePath(type);
    std::string resource_type_full_path = ConcatenatePath(resource_root_path_,
                                                          resource_type_path);

    std::string resource_full_path = ConcatenatePath(resource_type_full_path,
                                                     name);

    return resource_full_path;
}

}