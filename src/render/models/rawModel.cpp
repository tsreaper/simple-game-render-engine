#include "rawModel.h"

// Constructor
RawModel::RawModel(GLuint _vaoId, int _vertexCount)
{
    vaoId = _vaoId;
    vertexCount = _vertexCount;
}

// Get VAO id
GLuint RawModel::getVaoId() const
{
    return vaoId;
}

// Get number of vertex
int RawModel::getVertexCount() const
{
    return vertexCount;
}
