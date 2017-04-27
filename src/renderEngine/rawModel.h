#ifndef RAW_MODEL_H_
#define RAW_MODEL_H_

#include "../glew.h"

class RawModel
{
    public:
    
    RawModel(GLuint _vaoId, int _vertexCount);
    GLuint getVaoId();
    int getVertexCount();
    
    private:
    
    GLuint vaoId;
    int vertexCount;
};

#endif
