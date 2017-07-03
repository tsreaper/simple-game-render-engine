#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#include "thirdparty/lodepng/lodepng.h"
#include "render/resource/loader/textureLoader.h"

using namespace std;

// Create plain texture
PlainTexture* TextureLoader::loadPlainTexture(const char* name)
{
    GLuint id = loadTexture(("res/plain/" + string(name) + ".png").c_str());
    return new PlainTexture(name, id);
}

// Create model texture
ModelTexture* TextureLoader::loadModelTexture(const char* name)
{
    // Load texture file
    GLuint texId = loadTexture(("res/entity/" + string(name) + "/texture.png").c_str());

    // Read texture's config file
    ifstream config("res/entity/" + string(name) + "/config.txt");
    if (!config.is_open())
    {
        cerr << "ERROR: [TextureLoader::loadModelTexture] Cannot open texture config file" << name << "!" << endl;
        exit(-1);
    }

    float reflectivity = 0, shineDamper = 1;
    bool transparency = false;
    int atlasRows = 1;

    string s;
    float value;
    while (config >> s >> value)
    {
        if (s == "reflectivity")
            reflectivity = value;
        else if (s == "shineDamper")
            shineDamper = value;
        else if (s == "transparency")
            transparency = (value > 0.5);
        else if (s == "atlasRows")
            atlasRows = round(value);
        else
        {
            cerr << "ERROR: [TextureLoader::loadModelTexture] Unknown config property " << s << "!" << endl;
            exit(-1);
        }
    }

    return new ModelTexture(name, texId, reflectivity, shineDamper, transparency, atlasRows);
}

// Create terrain texture
TerrainTexture* TextureLoader::loadTerrainTexture(const char* name)
{
    GLuint k = loadTexture(("res/terrain/" + string(name) + "/k.png").c_str());
    GLuint r = loadTexture(("res/terrain/" + string(name) + "/r.png").c_str());
    GLuint g = loadTexture(("res/terrain/" + string(name) + "/g.png").c_str());
    GLuint b = loadTexture(("res/terrain/" + string(name) + "/b.png").c_str());
    GLuint blend = loadTexture(("res/terrain/" + string(name) + "/blend.png").c_str());

    return new TerrainTexture(name, k, r, g, b, blend);
}

// Create cube map texture
CubeMapTexture* TextureLoader::loadCubeMapTexture(const char* name)
{
    string filename[6] = {"posX.png", "negX.png", "posY.png", "negY.png", "posZ.png", "negZ.png"};
    unsigned error;
    unsigned char* image[6];
    unsigned int width[6], height[6];

    // Load image using lodepng
    for (int i = 0; i < 6; i++)
    {
        error = lodepng_decode32_file(&image[i], &width[i], &height[i], ("res/cube/" + string(name) + "/" + filename[i]).c_str());
        if (error)
        {
            cerr << "ERROR: [TextureLoader::loadCubeMapTexture] Failed to load cube map texture " << name << "!" << endl;
            exit(-1);
        }
    }

    // Generate cube map texture
    GLuint texId[1];
    glGenTextures(1, texId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texId[0]);
    for (int i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA, width[i], height[i], 0, GL_RGBA, GL_UNSIGNED_BYTE, image[i]);
        free(image[i]);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return new CubeMapTexture(name, texId[0]);
}

// Create texture from file
GLuint TextureLoader::loadTexture(const char* filename)
{
    unsigned error;
    unsigned char* image;
    unsigned int width, height;

    // Load image using lodepng
    error = lodepng_decode32_file(&image, &width, &height, filename);
    if (error)
    {
        cerr << "ERROR: [TextureLoader::loadTexture] Cannot load texture " << filename << "!" << endl;
        exit(-1);
    }

    // Generate texture
    GLuint texId[1];
    glGenTextures(1, texId);
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);

    free(image);
    return texId[0];
}
