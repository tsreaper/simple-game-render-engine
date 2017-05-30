#ifndef _MODEL_TEXTURE_H
#define _MODEL_TEXTURE_H

#include <string>
#include "../../../glew.h"

using namespace std;

// Texture of a model
class ModelTexture
{
public:

    // Constructor
    ModelTexture(const char* _name, GLuint id, float _reflectivity = 0, float _shineDamper = 1, bool _transparency = false, int _atlasRows = 1);

    // Destructor
    ~ModelTexture();

    // Get texture name
    const char* getName() const;

    // Get texture id
    GLuint getId() const;

    // Get reflectivity
    float getReflectivity() const;

    // Get shine damper
    float getShineDamper() const;

    // Get transparency
    bool getTransparency() const;

    // Get atlas rows
    int getAtlasRows() const;

    // Set reflectivity
    void setReflectivity(float _reflectivity);

    // Set shine damper
    void setShineDamper(float _shineDamper);

    // Set transparency
    void setTransparency(float _transparency);

private:

    // Texture name
    string name;

    // Texture id
    GLuint textureId;

    // Reflectivity
    float reflectivity;

    // Shine damper
    float shineDamper;

    // Transparency
    bool transparency;

    // Rows of atlas
    int atlasRows;
};

#endif
