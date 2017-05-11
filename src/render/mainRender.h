#ifndef MAIN_RENDER_H_
#define MAIN_RENDER_H_

#include <unordered_map>
#include <unordered_set>
#include "../glew.h"
#include "shaders/basicShader.h"
#include "shaders/staticShader.h"
#include "shaders/terrainShader.h"
#include "shaders/waterShader.h"
#include "shaders/skyboxShader.h"
#include "entities/entity.h"
#include "entities/light.h"
#include "entities/skybox.h"
#include "terrains/terrain.h"
#include "terrains/water.h"
#include "textures/waterFbo.h"

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
    
    // Create a water terrain in the 3D world
    static Water* createWater(int gridX, int gridZ, float y);
    
    // Remove the entity from the 3D world
    static void destroyEntity(Entity* entity);
    
    // Remove the terrain from the 3D world
    static void destroyTerrain(Terrain* terrain);
    
    // Remove the water terrain from the 3D world
    static void destroyWater(Water* water);
    
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
    static unordered_set<Water*> waterSet;
    static WaterFbo* waterFbo;
    static Skybox* skybox;
    
    // Shader program
    static StaticShader* staticShader;
    static TerrainShader* terrainShader;
    static WaterShader* waterShader;
    static SkyboxShader* skyboxShader;

    // Light in the 3D world
    static Light* light;
    
    // Render everything except water
    static void renderWithoutWater(const float* cameraMatrix, float clipHeight = -1e10, bool clipPositive = false);
    
    // Prepare shader for rendering
    static void prepareShader(BasicShader* shader, const float* cameraMatrix, float clipHeight, bool clipPositive);
};

#endif
