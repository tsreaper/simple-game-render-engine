#ifndef _MAIN_RENDER_H
#define _MAIN_RENDER_H

#include "glew.h"

#include "render/object/scene/scene.h"

#include "render/object/entity/entityRenderer.h"
#include "render/object/terrain/terrainRenderer.h"
#include "render/object/water/waterRenderer.h"
#include "render/object/skybox/skyboxRenderer.h"

#include "render/object/shader/basicShader.h"
#include "render/object/entity/entityShader.h"
#include "render/object/terrain/terrainShader.h"
#include "render/object/water/waterShader.h"
#include "render/object/skybox/skyboxShader.h"

#include "render/object/water/waterFbo.h"

class MainRender
{
public:

    // Initialize render
    static void init();

    // Main render process
    static void render();

    // Clean up
    static void cleanUp();

    // Get current scene
    static Scene* getScene();

    // Set current scene
    static void setScene(Scene* _scene);

private:

    // Field of view angle
    static const float FOV;

    // Near projection plane
    static const float Z_NEAR;

    // Far projection plane
    static const float Z_FAR;

    // Current scene
    static Scene* scene;

    // Renderers
    static EntityRenderer* entityRenderer;
    static TerrainRenderer* terrainRenderer;
    static WaterRenderer* waterRenderer;
    static SkyboxRenderer* skyboxRenderer;

    // Shader program
    static EntityShader* entityShader;
    static TerrainShader* terrainShader;
    static WaterShader* waterShader;
    static SkyboxShader* skyboxShader;

    // Water frame buffer object for water rendering
    static WaterFbo* waterFbo;

    // Render everything except water
    static void renderWithoutWater(const float* cameraMatrix, float clipHeight = -1e10, bool clipPositive = false);

    // Render water only
    static void renderWater(const float* cameraMatrix, const float* reflectionCameraMatrix);

    // Prepare shader for rendering
    static void prepareShader(BasicShader* shader, const float* cameraMatrix, float clipHeight = -1e10, bool clipPositive = false);
};

#endif
