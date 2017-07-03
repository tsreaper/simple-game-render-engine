#ifndef _SCENE_H
#define _SCENE_H

#include <unordered_map>
#include <unordered_set>

#include "utils/struct/struct.h"

#include "render/object/entity/entity.h"
#include "render/object/terrain/terrain.h"
#include "render/object/water/water.h"
#include "render/object/light/light.h"
#include "render/object/skybox/skybox.h"

using namespace std;

class Scene
{
public:

    // No water indicator
    static const float NO_WATER;

    // Constructor
    Scene(float _waterHeight = NO_WATER);

    // Destructor
    ~Scene();

    // Update scene
    void update();

    // Get water height
    float getWaterHeight() const;

    // Get sky color
    vec3 getSkyCol() const;

    // Get skybox
    Skybox* getSkybox() const;

    // Get all light
    const unordered_set<Light*>* getAllLight() const;

    // Get all entities
    const unordered_map<string, unordered_set<Entity*>>* getAllEntities() const;

    // Get all terrains
    const unordered_map<string, unordered_set<Terrain*>>* getAllTerrains() const;

    // Get all water
    const unordered_set<Water*>* getAllWater() const;

    // Set water height
    void setWaterHeight(float _waterHeight);

    // Set sky color
    void setSkyCol(vec3 _col);

    // Add light into scene
    Light* addLight(vec3 pos, vec3 col, vec3 att = vec3(1, 0, 0));

    // Add an entity into scene
    Entity* addEntity(
        const char* name, vec3 pos = vec3(0, 0, 0),
        vec3 rot = vec3(0, 0, 0), float scale = 1, int atlasPos = 0
    );

    // Add a terrain into scene
    Terrain* addTerrain(
        const char* name, int gridX, int gridZ,
        float minHeight, float maxHeight, const char* heightMapName
    );

    // Add water into scene
    Water* addWater(int gridX, int gridZ);

    // Delete light from scene
    void deleteLight(Light* light);

    // Delete an entity from scene
    void deleteEntity(Entity* entity);

    // Delete a terrain from scene
    void deleteTerrain(Terrain* terrain);

    // Delete water from scene
    void deleteWater(Water* water);

private:

    // Water height in the scene
    float waterHeight;

    // Sky color
    vec3 skyCol;

    // Skybox of the scene
    Skybox* sky;

    // Light in the scene
    unordered_set<Light*> lightSet;

    // Entity map
    unordered_map<string, unordered_set<Entity*>> entityMap;

    // Terrain map
    unordered_map<string, unordered_set<Terrain*>> terrainMap;

    // Water set
    unordered_set<Water*> waterSet;
};

#endif
