#include "glew.h"
#include "renderEngine/displayManager.h"
#include "renderEngine/rawModel.h"
#include "renderEngine/loader.h"
#include "renderEngine/renderer.h"
#include "shaders/staticShader.h"

float verticies[] = {
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
};

int indicies[] = {0, 1, 3, 3, 1, 2};

int main (int argc,  char** argv)
{
    DisplayManager::createDisplay();
    
    Loader loader;
    Renderer renderer;
    StaticShader shader;
    
    RawModel model = loader.loadToVao(verticies, 12, indicies, 6);
    
    while (!DisplayManager::isExiting())
    {
        renderer.prepare();
        shader.start();
        renderer.render(model);
        shader.stop();
        DisplayManager::updateDisplay();
    }
    
    shader.cleanUp();
    loader.cleanUp();
    DisplayManager::destroyDisplay();
    
    return 0;
}
