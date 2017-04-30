#ifndef TEXTURE_MODEL_H_
#define TEXTURE_MODEL_H_

#include <string>
#include "rawModel.h"
#include "../textures/modelTexture.h"

using namespace std;

// Model with texture
class TexturedModel
{
public:
    
    // Constructor
    TexturedModel(const char* _name, RawModel* _raw, ModelTexture* _texture);
    
    // Destructor
    ~TexturedModel();
    
    // Get model name
    const char* getName() const;
    
    // Get raw model pointer
    RawModel* getRaw() const;
    
    // Get texture pointer
    ModelTexture* getTexture() const;
    
private:
    
    // Model name
    string name;
    
    // Raw model pointer
    RawModel* raw;
    
    // Texture pointer
    ModelTexture* texture;
};

#endif
