#ifndef _OBJ_LOADER_H
#define _OBJ_LOADER_H

#include "../model/rawModel.h"

// Obj file loader
class ObjLoader
{
public:

    // Load an obj file
    static RawModel* loadObj(const char* name);
};

#endif
