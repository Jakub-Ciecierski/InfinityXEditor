#ifndef PROJECT_RESOURCE_MEMORY_CACHE_H
#define PROJECT_RESOURCE_MEMORY_CACHE_H

#include <memory>
#include <vector>

namespace ifx {

class Resource;

class ResourceMemoryCache {
public:
    ~ResourceMemoryCache();
    
    static ResourceMemoryCache& GetInstance();

    /**
     * Adds resources to cache.
     * Returns false if resource already exists.
     */
    bool Add(std::shared_ptr<Resource> resource);

    /**
     * Returns nullptr if resource does not exist.
     */
    std::shared_ptr<Resource> Get(std::string filepath);

    /**
     * Checks if resource already exists in cache.
     */
    bool Exists(std::string filepath);

    /**
     * Clear resources that are not currently used.
     */
    void ClearUnusedResources();

    /**
     * Clears entire cache.
     * Actual deleting of memory might be postponed untill
     * no other object uses that resource.
     */
    void ClearAll();

private:
    ResourceMemoryCache();

    std::vector<std::shared_ptr<Resource>> resources_;
};

}

#endif //PROJECT_RESOURCE_MEMORY_CACHE_H
