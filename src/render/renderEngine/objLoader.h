#ifndef OBJ_LOADER_H_
#define OBJ_LOADER_H_

#include "../models/texturedModel.h"

// Obj file loader
class ObjLoader
{
public:
    
    // Load an obj file
    static TexturedModel* loadObj(const char* objName);
};

#endif
