#ifndef _SKYBOX_RENDERER_H
#define _SKYBOX_RENDERER_H

#include "glew.h"
#include "render/object/skybox/skybox.h"
#include "render/object/skybox/skyboxShader.h"

// Skybox renderer
class SkyboxRenderer
{
public:

    // Render a skybox
    void render(const Skybox* skybox, SkyboxShader* shader);
};

#endif
