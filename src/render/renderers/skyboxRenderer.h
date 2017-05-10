#ifndef SKYBOX_RENDERER_H_
#define SKYBOX_RENDERER_H_

#include "../../glew.h"
#include "../entities/skybox.h"
#include "../shaders/skyboxShader.h"

// Skybox renderer
class SkyboxRenderer
{
public:
    
    // Render a skybox
    static void render(const Skybox* skybox, SkyboxShader* shader);
};

#endif
