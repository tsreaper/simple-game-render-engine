#include <iostream>
#include "scene.h"

using namespace std;

// No water indicator
const float Scene::NO_WATER = -1e10;

// Constructor
Scene::Scene(
    float sunX, float sunY, float sunZ,
    float sunR, float sunG, float sunB,
    float _waterHeight
): waterHeight(_waterHeight)
{
    sun = new Light(sunX, sunY, sunZ, sunR, sunG, sunB);
    sky = new Skybox();
}

// Destructor
Scene::~Scene()
{
    // Clean up entities
    for (auto i = entityMap.begin(); i != entityMap.end();)
    {
        auto nxti = next(i);
        for (auto j = i->second.begin(); j != i->second.end();)
        {
            auto nxtj = next(j);
            deleteEntity(*j);
            j = nxtj;
        }
        i = nxti;
    }

    // Clean up terrains
    for (auto i = terrainMap.begin(); i != terrainMap.end();)
    {
        auto nxti = next(i);
        for (auto j = i->second.begin(); j != i->second.end();)
        {
            auto nxtj = next(j);
            deleteTerrain(*j);
            j = nxtj;
        }
        i = nxti;
    }

    // Clean up water
    for (auto i = waterSet.begin(); i != waterSet.end();)
    {
        auto nxti = next(i);
        deleteWater(*i);
        i = nxti;
    }

    // Clean up sun light and skybox
    delete sun;
    delete sky;
}

// Update scene
void Scene::update()
{
    sky->rotate();
}

// Get water height
float Scene::getWaterHeight() const
{
    return waterHeight;
}

// Get sun light
Light* Scene::getSun() const
{
    return sun;
}

// Get skybox
Skybox* Scene::getSkybox() const
{
    return sky;
}

// Get all entities
const unordered_map<string, unordered_set<Entity*>>* Scene::getAllEntities() const
{
    return &entityMap;
}

// Get all terrains
const unordered_map<string, unordered_set<Terrain*>>* Scene::getAllTerrains() const
{
    return &terrainMap;
}

// Get all water
const unordered_set<Water*>* Scene::getAllWater() const
{
    return &waterSet;
}

// Set water height
void Scene::setWaterHeight(float _waterHeight)
{
    waterHeight = _waterHeight;
    for (Water* water : waterSet)
        water->setY(waterHeight);
}

// Set sun light
void Scene::setSun(float x, float y, float z, float r, float g, float b)
{
    delete sun;
    sun = new Light(x, y, z, r, g, b);
}

// Add an entity into scene
Entity* Scene::addEntity(
    const char* name, float tX, float tY, float tZ,
    float rX, float rY, float rZ, float scale, int atlasPos
)
{
    Entity* entity = new Entity(name, tX, tY, tZ, rX, rY, rZ, scale, atlasPos);
    if (entityMap.find(name) == entityMap.end())
        entityMap[name] = unordered_set<Entity*>();
    entityMap[name].insert(entity);
    return entity;
}

// Add a terrain into scene
Terrain* Scene::addTerrain(
    const char* name, int gridX, int gridZ,
    float minHeight, float maxHeight, const char* heightMapName
)
{
    Terrain* terrain = new Terrain(name, gridX, gridZ, minHeight, maxHeight, heightMapName);
    if (terrainMap.find(name) == terrainMap.end())
        terrainMap[name] = unordered_set<Terrain*>();
    terrainMap[name].insert(terrain);
    return terrain;
}

// Add water into scene
Water* Scene::addWater(int gridX, int gridZ)
{
    Water* water = new Water(gridX, gridZ, waterHeight);
    waterSet.insert(water);
    return water;
}

// Delete an entity from scene
void Scene::deleteEntity(Entity* entity)
{
    unordered_set<Entity*>& entitySet = entityMap[entity->getTexture()->getName()];
    entitySet.erase(entity);
    if (entitySet.empty())
        entityMap.erase(entity->getTexture()->getName());
    delete entity;
}

// Delete a terrain from scene
void Scene::deleteTerrain(Terrain* terrain)
{
    unordered_set<Terrain*>& terrainSet = terrainMap[terrain->getTexture()->getName()];
    terrainSet.erase(terrain);
    if (terrainSet.empty())
        terrainMap.erase(terrain->getTexture()->getName());
    delete terrain;
}

// Delete water from scene
void Scene::deleteWater(Water* water)
{
    waterSet.erase(water);
    delete water;
}
