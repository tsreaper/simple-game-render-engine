#ifndef MODEL_TEXTURE_H_
#define MODEL_TEXTURE_H_

#include <string>
#include "../../glew.h"

using namespace std;

// Texture of a model
class ModelTexture
{
public:
    
    // Constructor
    ModelTexture(const char* _name, GLuint id);
    
    // Destructor
    ~ModelTexture();
    
    // Get texture name
    const char* getName() const;
    
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
    
    // Texture name
    string name;
    
    // Texture id
    GLuint textureId;
    
    // Reflectivity
    float reflectivity;
    
    // Shine damper
    float shineDamper;
};

#endif
