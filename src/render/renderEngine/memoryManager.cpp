#include <iostream>
#include <fstream>
#include "loader.h"
#include "objLoader.h"
#include "memoryManager.h"

using namespace std;

// Model mapping file name
const char* MemoryManager::MODEL_MAPPING_FILE = "res/models.txt";

// Textured model info map
unordered_map<string, resInfo> MemoryManager::resMap;

// Pointer maps
unordered_map<string, refCount<TexturedModel>> MemoryManager::modelMap;
unordered_map<string, refCount<RawModel>> MemoryManager::rawMap;
unordered_map<string, refCount<ModelTexture>> MemoryManager::textureMap;

// Initialize memory manager
void MemoryManager::init()
{
    // Load model mapping file
    ifstream file(MODEL_MAPPING_FILE);
    if (!file.is_open())
    {
        cerr << "ERROR: [MemoryManager] Could not load model mapping file!" << endl;
        return;
    }
    
    string model, raw, texture;
    float reflectivity, shineDamper;
    while(!file.eof())
    {
        file >> model;
        if (model == "#")
            getline(file, model);
        else
        {
            file >> raw >> texture >> reflectivity >> shineDamper;
            resMap.insert(make_pair(model, resInfo(raw.c_str(), texture.c_str(), reflectivity, shineDamper)));
        }
    }
}

// Get textured model by model name
TexturedModel* MemoryManager::getTexturedModel(const char* modelName)
{
    if (resMap.find(modelName) == resMap.end())
    {
        cerr << "ERROR: [MemoryManager] Could not load textured model!" << endl;
        return NULL;
    }
    resInfo& info = resMap.at(modelName);
    
    if (modelMap.find(modelName) == modelMap.end())
    {
        RawModel* raw = getRawModel(info.raw.c_str());
        ModelTexture* texture = getModelTexture(info.texture.c_str(), info.reflectivity, info.shineDamper);
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
ModelTexture* MemoryManager::getModelTexture(const char* filename, float reflectivity, float shineDamper)
{
    if (textureMap.find(filename) == textureMap.end())
    {
        ModelTexture* texture = Loader::loadTexture(filename);
        texture->setReflectivity(reflectivity);
        texture->setShineDamper(shineDamper);
        textureMap.insert(make_pair(filename, refCount<ModelTexture>(texture, 1)));
    }
    else
        textureMap.at(filename).count++;
    
    return textureMap.at(filename).ptr;
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
