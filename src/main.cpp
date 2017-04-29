#include <iostream>
#include "glew.h"
#include "render/renderEngine/displayManager.h"
#include "render/renderEngine/loader.h"
#include "render/renderEngine/objLoader.h"
#include "render/renderEngine/renderer.h"
#include "render/shaders/staticShader.h"
#include "render/models/texturedModel.h"
#include "render/entities/entity.h"
#include "render/entities/light.h"
#include "logic/gameLogic.h"

int main (int argc,  char** argv)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    DisplayManager::createDisplay();
    
    StaticShader shader;
    Renderer::setShader(&shader);
    
    TexturedModel* model = ObjLoader::loadObj("dragon");
    Entity* entity = new Entity(model, 0, -5, -25);
    Light* light = new Light(0, 0, -20, 1, 1, 1);
    
    while (!DisplayManager::isExiting())
    {
        GameLogic::run();
        entity->incRotation(0, -0.01, 0);
        Renderer::prepare();
        Renderer::render(entity, light);
        DisplayManager::updateDisplay();
    }
    
    shader.cleanUp();
    Loader::cleanUp();
    DisplayManager::destroyDisplay();
    
    return 0;
}
