#ifndef RAW_MODEL_H_
#define RAW_MODEL_H_

#include <string>
#include "../../glew.h"

using namespace std;

// Model without texture
class RawModel
{
public:
    
    // Constructor
    RawModel(const char* _name, GLuint _vaoId, GLuint _vertexCount, int _vboCount = 4);
    
    // Destructor
    ~RawModel();
    
    // Get raw model name
    const char* getName() const;
    
    // Get VAO id
    int getVaoId() const;
    
    // Get number of vertex
    int getVertexCount() const;
    
    // Add a VBO id into list
    void addVboId(int pos, GLuint id);
    
private:
    
    // Raw model name
    string name;
    
    // VAO id
    GLuint vaoId;
    
    // Number of vertex
    int vertexCount;
    
    // VBO ids
    GLuint* vboIds;
    
    // Number of VBOs
    int vboCount;
};

#endif
