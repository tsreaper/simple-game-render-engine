#include <iostream>
#include "render/object/scene/scene.h"

using namespace std;

// No water indicator
const float Scene::NO_WATER = -1e10;

// Constructor
Scene::Scene(float _waterHeight): waterHeight(_waterHeight)
{
    sky = new Skybox("skyboxDay", "skyboxNight");
}

// Destructor
Scene::~Scene()
{
    // Clean up light
    for (auto i = lightSet.begin(); i != lightSet.end();)
    {
        auto nxti = next(i);
        deleteLight(*i);
        i = nxti;
    }

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

    // Clean up skybox
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

// Get sky color
vec3 Scene::getSkyCol() const
{
    return skyCol;
}

// Get skybox
Skybox* Scene::getSkybox() const
{
    return sky;
}

// Get all light
const unordered_set<Light*>* Scene::getAllLight() const
{
    return &lightSet;
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

// Set sky color
void Scene::setSkyCol(vec3 _col)
{
    skyCol = _col;
}

// Add light into scene
Light* Scene::addLight(vec3 pos, vec3 col, vec3 att)
{
    Light* light = new Light(pos, col, att);
    lightSet.insert(light);
    return light;
}

// Add an entity into scene
Entity* Scene::addEntity(
    const char* name, vec3 pos, vec3 rot, float scale, int atlasPos
)
{
    Entity* entity = new Entity(name, pos, rot, scale, atlasPos);
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

// Delete light from scene
void Scene::deleteLight(Light* light)
{
    lightSet.erase(light);
    delete light;
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
