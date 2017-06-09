#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include <unordered_map>

#include "render/resource/model/rawModel.h"
#include "render/resource/texture/plainTexture.h"
#include "render/resource/texture/modelTexture.h"
#include "render/resource/texture/terrainTexture.h"
#include "render/resource/texture/cubeMapTexture.h"

using namespace std;

// Reference counter
template <class T>
struct refCount
{
    T* ptr;
    int count;
    refCount(T* _ptr, int _count): ptr(_ptr), count(_count) {}
};

// RAM manager
class ResourceManager
{
public:

    // Get resource
    template <class T>
    static T* getResource(const char* name);

    // Delete resource
    template <class T>
    static void deleteResource(T* res);

private:

    // Pointer maps
    static unordered_map<string, refCount<RawModel>> rawModelMap;
    static unordered_map<string, refCount<PlainTexture>> plainTextureMap;
    static unordered_map<string, refCount<ModelTexture>> modelTextureMap;
    static unordered_map<string, refCount<TerrainTexture>> terrainTextureMap;
    static unordered_map<string, refCount<CubeMapTexture>> cubeMapTextureMap;

    // Get corresponding pointer map
    template <class T>
    static unordered_map<string, refCount<T>>* getResMap();

    // Load resource by loader
    template <class T>
    static T* loadResource(const char* name);
};

#include "render/resource/manager/resourceManager.tpp"

#endif
