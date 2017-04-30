#include <iostream>
#include "renderEngine/windowManager.h"
#include "renderEngine/memoryManager.h"
#include "renderEngine/renderer.h"
#include "mainRender.h"

using namespace std;

// Entity map
unordered_map<string ,unordered_set<Entity*>> MainRender::entityMap;

// Shader program
StaticShader* MainRender::shader = NULL;

// Light in the 3D world
Light* MainRender::light = NULL;

// Initialize render
void MainRender::init()
{
    WindowManager::createDisplay();
    MemoryManager::init();
    
    shader = new StaticShader();
}

// Main render process
void MainRender::render()
{
    Renderer::prepare();
    
    shader->start();
    for (auto entitySet : entityMap)
    {
        Renderer::bindTexturedModel((*(entitySet.second.begin()))->getModel(), shader);
        for (auto entity : entitySet.second)
            Renderer::render(entity, shader);
        Renderer::unbindTexturedModel();
    }
    shader->stop();
    
    WindowManager::updateDisplay();
}

// Create an entity in the 3D world
Entity* MainRender::createEntity(const char* name)
{
    // Create entity
    Entity* entity = new Entity(MemoryManager::getTexturedModel(name));
    
    // Record entity into map
    if (entityMap.find(name) == entityMap.end())
        entityMap[name] = unordered_set<Entity*>();
    entityMap[name].insert(entity);
    
    return entity;
}

// Remove the entity from the 3D world
void MainRender::destroyEntity(Entity* entity)
{
    unordered_set<Entity*>& entitySet = entityMap[entity->getModel()->getName()];
    entitySet.erase(entity);
    if (entitySet.empty())
        entityMap.erase(entity->getModel()->getName());
    delete entity;
}

// Load light
void MainRender::loadLight(Light* _light)
{
    light = _light;
    shader->start();
    shader->loadLightPos(light->getX(), light->getY(), light->getZ());
    shader->loadLightCol(light->getR(), light->getG(), light->getB());
    shader->stop();
}

// Clean up
void MainRender::cleanUp()
{
    for (auto entitySet : entityMap)
        for (auto entity : entitySet.second)
            destroyEntity(entity);
    
    delete light;
    
    shader->cleanUp();
    delete shader;
    
    WindowManager::destroyDisplay();
}
