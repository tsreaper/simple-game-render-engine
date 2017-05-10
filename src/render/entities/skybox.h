#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "../../glew.h"
#include "../models/rawModel.h"

class Skybox
{
public:
    
    // Size of the skybox
    static const float SIZE;
    
    // Rotation speed of the skybox
    static const float ROTATE_SPEED;
    
    // Constructor
    Skybox();
    
    // Destructor
    ~Skybox();
    
    // Get the rotation angle
    float getAngle() const;
    
    // Get the cube model
    RawModel* getRaw() const;
    
    // Get the texture id
    int getTextureId() const;
    
    // Rotate skybox
    void rotate();
    
private:
    
    // Raw cube model
    RawModel* cube;
    
    // Texture id
    GLuint textureId;
    
    // Rotation angle of the skybox
    float angle;
};

#endif
