#ifndef TEXTURE_MODEL_H_
#define TEXTURE_MODEL_H_

#include "rawModel.h"
#include "../textures/modelTexture.h"

// Model with texture
class TexturedModel
{
public:
    
    // Constructor
    TexturedModel(RawModel* _raw, ModelTexture* _texture);
    
    // Get raw model pointer
    RawModel* getRaw() const;
    
    // Get texture pointer
    ModelTexture* getTexture() const;
    
private:
    
    // Raw model pointer
    RawModel* raw;
    
    // Texture pointer
    ModelTexture* texture;
};

#endif
