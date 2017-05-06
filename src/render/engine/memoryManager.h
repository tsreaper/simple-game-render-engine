#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_

#include <unordered_map>
#include <unordered_set>
#include "../models/rawModel.h"
#include "../textures/modelTexture.h"
#include "../models/texturedModel.h"
#include "../textures/texturePack.h"

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
struct modelInfo
{
    string raw, texture;
    float reflectivity, shineDamper;
    bool transparency;
    modelInfo(
        const char* _raw, const char* _texture, float _reflectivity, float _shineDamper, bool _transparency
    ): raw(_raw), texture(_texture), reflectivity(_reflectivity), shineDamper(_shineDamper), transparency(_transparency) {}
};

// Texture pack info
struct packInfo
{
    string k, r, g, b, blend;
    packInfo(
        const char* _k, const char* _r, const char* _g, const char* _b, const char* _blend
    ): k(_k), r(_r), g(_g), b(_b), blend(_blend) {}
};

// CPU RAM manager
class MemoryManager
{
public:
    
    // Mapping file name
    static const char* MODEL_MAPPING_FILE;
    static const char* PACK_MAPPING_FILE;
    
    // Initialize memory manager
    static void init();
    
    // Get textured model by model name
    static TexturedModel* getTexturedModel(const char* modelName);
    
    // Get raw model by file name
    static RawModel* getRawModel(const char* filename);
    
    // Get model texture by file name
    static ModelTexture* getModelTexture(const char* filename, float reflectivity, float shineDamper, bool transparency);
    
    // Get texture pack by name
    static TexturePack* getTexturePack(const char* packName);
    
    // Delete textured model
    static void deleteTexturedModel(TexturedModel* model);
    
    // Delete raw model
    static void deleteRawModel(RawModel* raw);
    
    // Delete model texture
    static void deleteModelTexture(ModelTexture* texture);
    
    // Delete texture pack
    static void deleteTexturePack(TexturePack* pack);

private:
    
    // Resource info map
    static unordered_map<string, modelInfo> modelRes;
    static unordered_map<string, packInfo> packRes;
    
    // Pointer maps
    static unordered_map<string, refCount<TexturedModel>> modelMap;
    static unordered_map<string, refCount<RawModel>> rawMap;
    static unordered_map<string, refCount<ModelTexture>> textureMap;
    static unordered_map<string, refCount<TexturePack>> packMap;
    
    // Load model mapping file
    static void loadModelMapping();
    
    // Load texture pack mapping file
    static void loadPackMapping();
};

#endif
