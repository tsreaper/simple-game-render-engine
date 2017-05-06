#ifndef OBJ_LOADER_H_
#define OBJ_LOADER_H_

#include "../models/rawModel.h"

// Obj file loader
class ObjLoader
{
public:
    
    // Load an obj file
    static RawModel* loadObj(const char* objFile);
};

#endif
