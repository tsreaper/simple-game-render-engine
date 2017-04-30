#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_

#include <unordered_map>
#include <unordered_set>
#include "../models/rawModel.h"
#include "../textures/modelTexture.h"
#include "../models/texturedModel.h"

using namespace std;

// Reference counter
template<class T>
struct refCount
{
    T* ptr;
    int count;
    refCount(T* _ptr, int _count): ptr(_ptr), count(_count) {}
};

// Textured model info
struct resInfo
{
    string raw, texture;
    float reflectivity, shineDamper;
    resInfo(
        const char* _raw, const char* _texture, float _reflectivity, float _shineDamper
    ): raw(_raw), texture(_texture), reflectivity(_reflectivity), shineDamper(_shineDamper) {}
};

// CPU RAM manager
class MemoryManager
{
public:
    
    // Model mapping file name
    static const char* MODEL_MAPPING_FILE;
    
    // Initialize memory manager
    static void init();
    
    // Get textured model by model name
    static TexturedModel* getTexturedModel(const char* modelName);
    
    // Get raw model by file name
    static RawModel* getRawModel(const char* filename);
    
    // Get model texture by file name
    static ModelTexture* getModelTexture(const char* filename, float reflectivity, float shineDamper);
    
    // Delete textured model
    static void deleteTexturedModel(TexturedModel* model);
    
    // Delete raw model
    static void deleteRawModel(RawModel* raw);
    
    // Delete model texture
    static void deleteModelTexture(ModelTexture* texture);

private:
    
    // Textured model info map
    static unordered_map<string, resInfo> resMap;
    
    // Pointer maps
    static unordered_map<string, refCount<TexturedModel>> modelMap;
    static unordered_map<string, refCount<RawModel>> rawMap;
    static unordered_map<string, refCount<ModelTexture>> textureMap;
};

#endif
