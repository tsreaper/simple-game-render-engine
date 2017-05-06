#ifndef MAIN_RENDER_H_
#define MAIN_RENDER_H_

#include <unordered_map>
#include <unordered_set>
#include "../glew.h"
#include "shaders/staticShader.h"
#include "shaders/terrainShader.h"
#include "entities/entity.h"
#include "entities/light.h"
#include "terrains/terrain.h"

using namespace std;

class MainRender
{
public:
    
    // Initialize render
    static void init();
    
    // Main render process
    static void render();
    
    // Create an entity in the 3D world
    static Entity* createEntity(const char* name);
    
    // Create a terrain in the 3D world
    static Terrain* createTerrain(const char* name, int gridX, int gridZ);
    
    // Remove the entity from the 3D world
    static void destroyEntity(Entity* entity);
    
    // Remove the terrain from the 3D world
    static void destroyTerrain(Terrain* terrain);
    
    // Load light
    static void loadLight(Light* _light);
    
    // Clean up
    static void cleanUp();
    
private:
    
    // Field of view angle
    static const float FOV;

    // Near projection plane
    static const float Z_NEAR;

    // Far projection plane
    static const float Z_FAR;
    
    // Objects being rendered
    static unordered_map<string, unordered_set<Entity*>> entityMap;
    static unordered_set<Terrain*> terrainSet;
    
    // Shader program
    static StaticShader* staticShader;
    static TerrainShader* terrainShader;

    // Light in the 3D world
    static Light* light;
};

#endif
