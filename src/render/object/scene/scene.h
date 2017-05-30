#ifndef _SCENE_H
#define _SCENE_H

#include <unordered_map>
#include <unordered_set>
#include "../entity/entity.h"
#include "../terrain/terrain.h"
#include "../water/water.h"
#include "../light/light.h"
#include "../skybox/skybox.h"

using namespace std;

class Scene
{
public:

    // No water indicator
    static const float NO_WATER;

    // Constructor
    Scene(
        float sunX = 0, float sunY = 1e5, float sunZ = 0,
        float sunR = 1, float sunG = 1, float sunB = 1,
        float _waterHeight = -1e10
    );

    // Destructor
    ~Scene();

    // Update scene
    void update();

    // Get water height
    float getWaterHeight() const;

    // Get sun light
    Light* getSun() const;

    // Get skybox
    Skybox* getSkybox() const;

    // Get all entities
    const unordered_map<string, unordered_set<Entity*>>* getAllEntities() const;

    // Get all terrains
    const unordered_map<string, unordered_set<Terrain*>>* getAllTerrains() const;

    // Get all water
    const unordered_set<Water*>* getAllWater() const;

    // Set water height
    void setWaterHeight(float _waterHeight);

    // Set sun light
    void setSun(float x, float y, float z, float r, float g, float b);

    // Add an entity into scene
    Entity* addEntity(
        const char* name, float tX = 0, float tY = 0, float tZ = 0,
        float rX = 0, float rY = 0, float rZ = 0, float scale = 1, int atlasPos = 0
    );

    // Add a terrain into scene
    Terrain* addTerrain(
        const char* name, int gridX, int gridZ,
        float minHeight, float maxHeight, const char* heightMapName
    );

    // Add water into scene
    Water* addWater(int gridX, int gridZ);

    // Delete an entity from scene
    void deleteEntity(Entity* entity);

    // Delete a terrain from scene
    void deleteTerrain(Terrain* terrain);

    // Delete water from scene
    void deleteWater(Water* water);

private:

    // Water height in the scene
    float waterHeight;

    // Sun(main light) in the scene
    Light* sun;

    // Skybox of the scene
    Skybox* sky;

    // Entity map
    unordered_map<string, unordered_set<Entity*>> entityMap;

    // Terrain map
    unordered_map<string, unordered_set<Terrain*>> terrainMap;

    // Water set
    unordered_set<Water*> waterSet;
};

#endif
