#ifndef ENTITY_H_
#define ENTITY_H_

#include "../models/texturedModel.h"

// Entity in the 3D world
class Entity
{
public:
    // Constructor
    Entity(TexturedModel* _model, float _tX, float _tY, float _tZ);
    
    // Increase position
    void incPosition(float x, float y, float z);
    
    // Increase rotation
    void incRotation(float x, float y, float z);
    
    // Get model
    TexturedModel* getModel() const;
    
    // Get X coordinate
    float getTX() const;
    
    // Get Y coordinate
    float getTY() const;
    
    // Get Z coordinate
    float getTZ() const;
    
    // Get X rotation
    float getRX() const;
    
    // Get Y rotation
    float getRY() const;
    
    // Get Z rotation
    float getRZ() const;
    
    // Get scaling factor
    float getScale() const;
    
    // Set X coordinate
    void setTX(float _tX);
    
    // Set Y coordinate
    void setTY(float _tY);
    
    // Set Z coordinate
    void setTZ(float _tZ);
    
    // Set X rotation
    void setRX(float _rX);
    
    // Set Y rotation
    void setRY(float _rY);
    
    // Set Z rotation
    void setRZ(float _rZ);
    
    // Set scaling factor
    void setScale(float _scale);

private:
    
    // Entity model
    TexturedModel* model;
    
    // XYZ coordinates
    float tX, tY, tZ;
    
    // XYZ rotations
    float rX, rY, rZ;
    
    // Scaling factor
    float scale;
};

#endif
