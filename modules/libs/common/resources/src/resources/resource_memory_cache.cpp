#include "resources/resource_memory_cache.h"

#include "resources/resource.h"

namespace ifx {

ResourceMemoryCache::ResourceMemoryCache() {}

ResourceMemoryCache::~ResourceMemoryCache() {}

ResourceMemoryCache& ResourceMemoryCache::GetInstance(){
    static ResourceMemoryCache instance;
    return instance;
}

bool ResourceMemoryCache::Add(std::shared_ptr<Resource> resource){
    if(Exists(resource->filepath()))
        return false;
    resources_.push_back(resource);
}

std::shared_ptr<Resource> ResourceMemoryCache::Get(std::string filepath){
    for(auto& resource : resources_){
        if(!filepath.compare(resource->filepath()))
            return resource;
    }
    return nullptr;
}

bool ResourceMemoryCache::Exists(std::string filepath){
    for(auto& resource : resources_){
        if(!filepath.compare(resource->filepath()))
            return true;
    }
    return false;
}

void ResourceMemoryCache::ClearUnusedResources(){
    std::vector<std::shared_ptr<Resource>> tmp_resources;

    for(auto& resource : resources_){
        if(resource.use_count() > 1)
            tmp_resources.push_back(resource);
    }

    resources_ = tmp_resources;
}

void ResourceMemoryCache::ClearAll(){
    resources_.clear();
}


    

}