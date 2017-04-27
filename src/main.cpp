#include "glew.h"
#include "renderEngine/displayManager.h"
#include "renderEngine/loader.h"
#include "renderEngine/renderer.h"
#include "shaders/staticShader.h"
#include "models/rawModel.h"

float verticies[] = {
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
};
int indicies[] = {0, 1, 3, 3, 1, 2};
float texCoords[] = {0, 0, 0, 1, 1, 1, 1, 0};

int main (int argc,  char** argv)
{
    DisplayManager::createDisplay();
    
    Loader loader;
    Renderer renderer;
    StaticShader shader;
    
    RawModel raw = loader.loadToVao(verticies, 12, texCoords, 8, indicies, 6);
    ModelTexture texture(loader.loadTexture("res/sample.png"));
    TexturedModel model(&raw, &texture);
    
    while (!DisplayManager::isExiting())
    {
        renderer.prepare();
        shader.start();
        renderer.render(&model);
        shader.stop();
        DisplayManager::updateDisplay();
    }
    
    shader.cleanUp();
    loader.cleanUp();
    DisplayManager::destroyDisplay();
    
    return 0;
}
