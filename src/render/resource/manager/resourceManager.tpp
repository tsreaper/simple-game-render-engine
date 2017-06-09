#include <iostream>
#include <fstream>
#include <typeinfo>

#include "render/resource/loader/modelLoader.h"
#include "render/resource/loader/objLoader.h"
#include "render/resource/loader/textureLoader.h"

using namespace std;

// Get resource
template <class T>
inline T* ResourceManager::getResource(const char* name)
{
    unordered_map<string, refCount<T>>* resMap = getResMap<T>();

    if (resMap->find(name) == resMap->end())
    {
        T* res = loadResource<T>(name);
        resMap->insert(make_pair(name, refCount<T>(res, 1)));
        cerr << "INFO: [ResourceManager::getResource] Creating new resource " + string(name) + "(" + typeid(res).name() + ")." << endl;
    }
    else
        resMap->at(name).count++;

    return resMap->at(name).ptr;
}

// Delete resource
template <class T>
inline void ResourceManager::deleteResource(T* res)
{
    unordered_map<string, refCount<T>>* resMap = getResMap<T>();
    auto it = resMap->find(res->getName());
    (*it).second.count--;
    if ((*it).second.count == 0)
    {
        cerr << "INFO: [ResourceManager::deleteResource] Releasing resource " + string(res->getName()) + "(" + typeid(res).name() + ")." << endl;
        resMap->erase(it);
        delete res;
    }
}

// Get corresponding pointer map
template <>
inline unordered_map<string, refCount<RawModel>>* ResourceManager::getResMap()
{
    return &rawModelMap;
}

template <>
inline unordered_map<string, refCount<PlainTexture>>* ResourceManager::getResMap()
{
    return &plainTextureMap;
}

template <>
inline unordered_map<string, refCount<ModelTexture>>* ResourceManager::getResMap()
{
    return &modelTextureMap;
}

template <>
inline unordered_map<string, refCount<TerrainTexture>>* ResourceManager::getResMap()
{
    return &terrainTextureMap;
}

template <>
inline unordered_map<string, refCount<CubeMapTexture>>* ResourceManager::getResMap()
{
    return &cubeMapTextureMap;
}

// Load resource by loader
template <>
inline RawModel* ResourceManager::loadResource(const char* name)
{
    return ObjLoader::loadObj(name);
}

template <>
inline PlainTexture* ResourceManager::loadResource(const char* name)
{
    return TextureLoader::loadPlainTexture(name);
}

template <>
inline ModelTexture* ResourceManager::loadResource(const char* name)
{
    return TextureLoader::loadModelTexture(name);
}

template <>
inline TerrainTexture* ResourceManager::loadResource(const char* name)
{
    return TextureLoader::loadTerrainTexture(name);
}

template <>
inline CubeMapTexture* ResourceManager::loadResource(const char* name)
{
    return TextureLoader::loadCubeMapTexture(name);
}
