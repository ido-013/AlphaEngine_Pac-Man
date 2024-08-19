#include "ResourceManager.h"

ResourceManager* ResourceManager::ptr = nullptr;

ResourceManager::~ResourceManager() 
{
    UnloadAllResource();
}

ResourceManager* ResourceManager::GetRMPtr()
{
    if (!ptr)
    {
        ptr = new ResourceManager;
    }

    return ptr;
}

void ResourceManager::DeleteRMPtr()
{
    if (ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

void ResourceManager::UnloadResource(const std::string& filename)
{
    auto it = resources.find(filename);

    if (it != resources.end())
    {
        Resource* res = it->second;
        res->SetCounter(res->GetCounter() - 1);

        if (res->GetCounter() == 0)
        {
            res->UnloadData();
            delete res;
            resources.erase(it);
        }
    }
}

void ResourceManager::UnloadAllResource()
{
    for (auto it = resources.begin(); it != resources.end(); it++)
    {
        it->second->UnloadData();
        delete it->second;
    }

    resources.clear();
}
