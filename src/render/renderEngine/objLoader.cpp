#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "loader.h"
#include "../models/rawModel.h"
#include "../textures/modelTexture.h"
#include "objLoader.h"

using namespace std;

// Load an obj file
TexturedModel* ObjLoader::loadObj(const char* objName)
{
    // Load obj from file
    ifstream obj("res/" + string(objName) + ".obj");
    
    if (!obj.is_open())
    {
        cerr << "ERROR: Could not load file " << "res/" + string(objName) + ".obj" << "!" << endl;
        return NULL;
    }
    
    // Read obj file
    vector<float*> v, vt, vn;
    vector<string*> f;
    unordered_map<string, int> mp;
    string t, fa, fb, fc;
    float x, y, z;
    
    while(!obj.eof())
    {
        obj >> t;
        if (t == "v")
        {
            // Vertex
            obj >> x >> y >> z;
            v.push_back(new float[3] {x, y, z});
        }
        else if (t == "vt")
        {
            // Texture coordinate
            obj >> x >> y;
            vt.push_back(new float[2] {x, 1-y});
        }
        else if (t == "vn")
        {
            // Vertex normal
            vn.push_back(new float[3] {x, y, z});
        }
        else if (t == "f")
        {
            // Faces
            obj >> fa >> fb >> fc;
            f.push_back(new string[3] {fa, fb, fc});
            if (mp.find(fa) == mp.end())
                mp.insert(make_pair(fa, mp.size()));
            if (mp.find(fb) == mp.end())
                mp.insert(make_pair(fb, mp.size()));
            if (mp.find(fc) == mp.end())
                mp.insert(make_pair(fc, mp.size()));
        }
        else
            getline(obj, t);
    }
    obj.close();
    
    // Calculate position, texture coordinates and indicies
    float* verticies = new float[mp.size()*3];
    float* texCoords = new float[mp.size()*2];
    int* indicies = new int[f.size()*3];
    
    int a, b, c;
    for (int i = 0; i < f.size(); i++)
        for (int j = 0; j < 3; j++)
        {
            int id = mp[f[i][j]];
            indicies[i*3+j] = id;
            sscanf(f[i][j].c_str(), "%d/%d/%d", &a, &b, &c);
            for (int k = 0; k < 3; k++)
                verticies[id*3+k] = v[a-1][k];
            for (int k = 0; k < 2; k++)
                texCoords[id*2+k] = vt[b-1][k];
        }
    
    // Put information into raw model
    RawModel *raw = Loader::loadToVao(verticies, mp.size()*3, texCoords, mp.size()*2, indicies, f.size()*3);
    
    // Load texture
    ModelTexture* texture = new ModelTexture(Loader::loadTexture(("res/" + string(objName) + "Texture.png").c_str()));
    TexturedModel* model = new TexturedModel(raw, texture);
    
    // Clean up
    for (int i = 0; i < v.size(); i++)
        delete[] v[i];
    for (int i = 0; i < vt.size(); i++)
        delete[] vt[i];
    for (int i = 0; i < vn.size(); i++)
        delete[] vn[i];
    for (int i = 0; i < f.size(); i++)
        delete[] f[i];
    
    return model;
}
