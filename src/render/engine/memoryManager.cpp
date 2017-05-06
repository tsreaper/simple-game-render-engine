#include <iostream>
#include <fstream>
#include "loader.h"
#include "objLoader.h"
#include "memoryManager.h"

using namespace std;

// Mapping file name
const char* MemoryManager::MODEL_MAPPING_FILE = "res/models.txt";
const char* MemoryManager::PACK_MAPPING_FILE = "res/packs.txt";

// Resource info map
unordered_map<string, modelInfo> MemoryManager::modelRes;
unordered_map<string, packInfo> MemoryManager::packRes;

// Pointer maps
unordered_map<string, refCount<TexturedModel>> MemoryManager::modelMap;
unordered_map<string, refCount<RawModel>> MemoryManager::rawMap;
unordered_map<string, refCount<ModelTexture>> MemoryManager::textureMap;
unordered_map<string, refCount<TexturePack>> MemoryManager::packMap;

// Initialize memory manager
void MemoryManager::init()
{
    loadModelMapping();
    loadPackMapping();
}

// Get textured model by model name
TexturedModel* MemoryManager::getTexturedModel(const char* modelName)
{
    if (modelRes.find(modelName) == modelRes.end())
    {
        cerr << "ERROR: [MemoryManager] Could not load textured model!" << endl;
        return NULL;
    }
    modelInfo& info = modelRes.at(modelName);
    
    if (modelMap.find(modelName) == modelMap.end())
    {
        RawModel* raw = getRawModel(info.raw.c_str());
        ModelTexture* texture = getModelTexture(info.texture.c_str(), info.reflectivity, info.shineDamper, info.transparency);
        TexturedModel* model = new TexturedModel(modelName, raw, texture);
        modelMap.insert(make_pair(modelName, refCount<TexturedModel>(model, 1)));
    }
    else
        modelMap.at(modelName).count++;
    
    return modelMap.at(modelName).ptr;
}

// Get raw model by file name
RawModel* MemoryManager::getRawModel(const char* filename)
{
    if (rawMap.find(filename) == rawMap.end())
    {
        RawModel* raw = ObjLoader::loadObj(filename);
        rawMap.insert(make_pair(filename, refCount<RawModel>(raw, 1)));
    }
    else
        rawMap.at(filename).count++;
    
    return rawMap.at(filename).ptr;
}

// Get model texture by file name
ModelTexture* MemoryManager::getModelTexture(const char* filename, float reflectivity, float shineDamper, bool transparency)
{
    if (textureMap.find(filename) == textureMap.end())
    {
        ModelTexture* texture = Loader::loadTexture(filename);
        texture->setReflectivity(reflectivity);
        texture->setShineDamper(shineDamper);
        texture->setTransparency(transparency);
        textureMap.insert(make_pair(filename, refCount<ModelTexture>(texture, 1)));
    }
    else
        textureMap.at(filename).count++;
    
    return textureMap.at(filename).ptr;
}

// Get texture pack by name
TexturePack* MemoryManager::getTexturePack(const char* packName)
{
    if (packRes.find(packName) == packRes.end())
    {
        cerr << "ERROR: [MemoryManager] Could not load texture pack!" << endl;
        return NULL;
    }
    packInfo& info = packRes.at(packName);
    
    if (packMap.find(packName) == packMap.end())
    {
        ModelTexture* k = getModelTexture(info.k.c_str(), 0, 1, false);
        ModelTexture* r = getModelTexture(info.r.c_str(), 0, 1, false);
        ModelTexture* g = getModelTexture(info.g.c_str(), 0, 1, false);
        ModelTexture* b = getModelTexture(info.b.c_str(), 0, 1, false);
        ModelTexture* blend = getModelTexture(info.blend.c_str(), 0, 1, false);
        TexturePack* pack = new TexturePack(packName, k, r, g, b, blend);
        packMap.insert(make_pair(packName, refCount<TexturePack>(pack, 1)));
    }
    else
        packMap.at(packName).count++;
    
    return packMap.at(packName).ptr;
}

// Delete textured model
void MemoryManager::deleteTexturedModel(TexturedModel* model)
{
    auto it = modelMap.find(model->getName());
    (*it).second.count--;
    if ((*it).second.count == 0)
    {
        modelMap.erase(it);
        delete model;
    }
}

// Delete raw model
void MemoryManager::deleteRawModel(RawModel* raw)
{
    auto it = rawMap.find(raw->getName());
    (*it).second.count--;
    if ((*it).second.count == 0)
    {
        rawMap.erase(it);
        delete raw;
    }
}

// Delete model texture
void MemoryManager::deleteModelTexture(ModelTexture* texture)
{
    auto it = textureMap.find(texture->getName());
    (*it).second.count--;
    if ((*it).second.count == 0)
    {
        textureMap.erase(it);
        delete texture;
    }
}

// Delete texture pack
void MemoryManager::deleteTexturePack(TexturePack* pack)
{
    auto it = packMap.find(pack->getName());
    (*it).second.count--;
    if ((*it).second.count == 0)
    {
        packMap.erase(it);
        delete pack;
    }
}

// Load model mapping file
void MemoryManager::loadModelMapping()
{
    ifstream file(MODEL_MAPPING_FILE);
    if (!file.is_open())
    {
        cerr << "ERROR: [MemoryManager] Could not load model mapping file!" << endl;
        return;
    }
    
    string model, raw, texture;
    float reflectivity, shineDamper;
    bool transparency;
    while(!file.eof())
    {
        file >> model;
        if (model == "#")
            getline(file, model);
        else
        {
            file >> raw >> texture >> reflectivity >> shineDamper >> transparency;
            modelRes.insert(make_pair(model, modelInfo(raw.c_str(), texture.c_str(), reflectivity, shineDamper, transparency)));
        }
    }
}

// Load terrain mapping file
void MemoryManager::loadPackMapping()
{
    ifstream file(PACK_MAPPING_FILE);
    if (!file.is_open())
    {
        cerr << "ERROR: [MemoryManager] Could not load pack mapping file!" << endl;
        return;
    }
    
    string pack, k, r, g, b, blend;
    while(!file.eof())
    {
        file >> pack;
        if (pack == "#")
            getline(file, pack);
        else
        {
            file >> k >> r >> g >> b >> blend;
            packRes.insert(make_pair(pack, packInfo(
                k.c_str(), r.c_str(), g.c_str(), b.c_str(), blend.c_str()
            )));
        }
    }
}
