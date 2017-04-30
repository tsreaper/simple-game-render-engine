#ifndef MAIN_RENDER_H_
#define MAIN_RENDER_H_

#include <unordered_map>
#include <unordered_set>
#include "../glew.h"
#include "shaders/staticShader.h"
#include "entities/entity.h"
#include "entities/light.h"

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
    
    // Remove the entity from the 3D world
    static void destroyEntity(Entity* entity);
    
    // Load light
    static void loadLight(Light* _light);
    
    // Clean up
    static void cleanUp();
    
private:
    
    // Entity map
    static unordered_map<string ,unordered_set<Entity*>> entityMap;
    
    // Shader program
    static StaticShader* shader;

    // Light in the 3D world
    static Light* light;
};

#endif
