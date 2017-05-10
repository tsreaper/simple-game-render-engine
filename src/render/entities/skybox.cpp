#include "../engine/loader.h"
#include "skybox.h"

// Size of the skybox
const float Skybox::SIZE = 500;

// Rotation speed of the skybox
const float Skybox::ROTATE_SPEED = 0.0005;

// Constructor
Skybox::Skybox()
{
    float vertices[] = {
        -SIZE, SIZE, -SIZE,
	    -SIZE, -SIZE, -SIZE,
	    SIZE, -SIZE, -SIZE,
        SIZE, -SIZE, -SIZE,
        SIZE, SIZE, -SIZE,
	    -SIZE, SIZE, -SIZE,
        
	    -SIZE, -SIZE, SIZE,
	    -SIZE, -SIZE, -SIZE,
	    -SIZE, SIZE, -SIZE,
	    -SIZE, SIZE, -SIZE,
	    -SIZE, SIZE, SIZE,
	    -SIZE, -SIZE, SIZE,
        
	    SIZE, -SIZE, -SIZE,
	    SIZE, -SIZE, SIZE,
	    SIZE, SIZE, SIZE,
	    SIZE, SIZE, SIZE,
	    SIZE, SIZE, -SIZE,
	    SIZE, -SIZE, -SIZE,
        
	    -SIZE, -SIZE, SIZE,
	    -SIZE, SIZE, SIZE,
	    SIZE, SIZE, SIZE,
	    SIZE, SIZE, SIZE,
	    SIZE, -SIZE, SIZE,
	    -SIZE, -SIZE, SIZE,
        
	    -SIZE, SIZE, -SIZE,
	    SIZE, SIZE, -SIZE,
	    SIZE, SIZE, SIZE,
	    SIZE, SIZE, SIZE,
	    -SIZE, SIZE, SIZE,
	    -SIZE, SIZE, -SIZE,
        
	    -SIZE, -SIZE, -SIZE,
	    -SIZE, -SIZE, SIZE,
	    SIZE, -SIZE, -SIZE,
	    SIZE, -SIZE, -SIZE,
	    -SIZE, -SIZE, SIZE,
	    SIZE, -SIZE, SIZE
    };
    
    const char* texName[] = {
        "skybox/right.png", "skybox/left.png", "skybox/top.png",
        "skybox/bottom.png", "skybox/back.png", "skybox/front.png"
    };
    
    cube = Loader::loadVertices("skybox", vertices, 108);
    textureId = Loader::loadCubeMapTexture(texName);
    
    angle = 0;
}

// Destructor
Skybox::~Skybox()
{
    delete cube;
    glDeleteTextures(1, &textureId);
}

// Get the rotation angle
float Skybox::getAngle() const
{
    return angle;
}

// Get the cube model
RawModel* Skybox::getRaw() const
{
    return cube;
}

// Get the texture id
int Skybox::getTextureId() const
{
    return textureId;
}

// Rotate skybox
void Skybox::rotate()
{
    angle += ROTATE_SPEED;
}
