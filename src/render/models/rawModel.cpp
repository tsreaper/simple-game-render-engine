#include "rawModel.h"

// Constructor
RawModel::RawModel(const char* _name, GLuint _vaoId, GLuint _vertexCount)
{
    name = _name;
    vaoId = _vaoId;
    vertexCount = _vertexCount;
    vboIds = new GLuint[4];
}

// Destructor
RawModel::~RawModel()
{
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(4, vboIds);
    delete[] vboIds;
}

// Get raw model name
const char* RawModel::getName() const
{
    return name.c_str();
}

// Get VAO id
int RawModel::getVaoId() const
{
    return vaoId;
}

// Get number of vertex
int RawModel::getVertexCount() const
{
    return vertexCount;
}

// Add a VBO id into list
void RawModel::addVboId(int pos, GLuint id)
{
    vboIds[pos] = id;
}
