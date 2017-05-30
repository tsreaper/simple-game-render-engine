#include "resourceManager.h"

// Pointer maps
unordered_map<string, refCount<RawModel>> ResourceManager::rawModelMap;
unordered_map<string, refCount<PlainTexture>> ResourceManager::plainTextureMap;
unordered_map<string, refCount<ModelTexture>> ResourceManager::modelTextureMap;
unordered_map<string, refCount<TerrainTexture>> ResourceManager::terrainTextureMap;
unordered_map<string, refCount<CubeMapTexture>> ResourceManager::cubeMapTextureMap;
