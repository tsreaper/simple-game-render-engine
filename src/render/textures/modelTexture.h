#ifndef MODEL_TEXTURE_H_
#define MODEL_TEXTURE_H_

// Texture of a model
class ModelTexture
{
public:
    
    // Constructor
    ModelTexture(int id);
    
    // Get texture id
    int getId() const;
    
private:
    
    // Texture id
    int textureId;
};

#endif
