#include "rawModel.h"

RawModel::RawModel(GLuint _vaoId, int _vertexCount)
{
    vaoId = _vaoId;
    vertexCount = _vertexCount;
}

GLuint RawModel::getVaoId()
{
    return vaoId;
}

int RawModel::getVertexCount()
{
    return vertexCount;
}
