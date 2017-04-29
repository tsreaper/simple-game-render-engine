#ifndef MODEL_TEXTURE_H_
#define MODEL_TEXTURE_H_

// Texture of a model
class ModelTexture
{
public:
    
    // Constructor
    ModelTexture(int id, float _reflectivity, float _shineDamper);
    
    // Get texture id
    int getId() const;
    
    // Get reflectivity
    float getReflectivity() const;

    // Get shine damper
    float getShineDamper() const;

    // Set reflectivity
    void setReflectivity(float _reflectivity);

    // Set shine damper
    void setShineDamper(float _shineDamper);
    
private:
    
    // Texture id
    int textureId;
    
    // Reflectivity
    float reflectivity;
    
    // Shine damper
    float shineDamper;
};

#endif
