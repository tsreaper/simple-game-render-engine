#ifndef RAW_MODEL_H_
#define RAW_MODEL_H_

#include "../../glew.h"

// Model without texture
class RawModel
{
public:
    
    // Constructor
    RawModel(GLuint _vaoId, int _vertexCount);
    
    // Get VAO id
    GLuint getVaoId() const;
    
    // Get number of vertex
    int getVertexCount() const;
    
private:
    
    // VAO id
    GLuint vaoId;
    
    // Number of vertex
    int vertexCount;
};

#endif
