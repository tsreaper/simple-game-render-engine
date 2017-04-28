#include "glew.h"
#include "render/renderEngine/displayManager.h"
#include "render/renderEngine/loader.h"
#include "render/renderEngine/objLoader.h"
#include "render/renderEngine/renderer.h"
#include "render/shaders/staticShader.h"
#include "render/models/texturedModel.h"
#include "render/entities/entity.h"
#include "logic/gameLogic.h"

int main (int argc,  char** argv)
{
    DisplayManager::createDisplay();
    
    StaticShader shader;
    Renderer::setShader(&shader);
    
    TexturedModel* model = ObjLoader::loadObj("stall");
    Entity* entity = new Entity(model, 0, -3, -7);
    
    while (!DisplayManager::isExiting())
    {
        GameLogic::run();
        entity->incRotation(0, -0.01, 0);
        Renderer::prepare();
        Renderer::render(entity);
        DisplayManager::updateDisplay();
    }
    
    shader.cleanUp();
    Loader::cleanUp();
    DisplayManager::destroyDisplay();
    
    return 0;
}
