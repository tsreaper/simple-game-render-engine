#ifndef _BASIC_SHADER_H
#define _BASIC_SHADER_H

#include "../../../glew.h"
#include "../light/light.h"
#include "shaderProgram.h"

// Basic shader for models
class BasicShader : public ShaderProgram
{
public:

    // Shader functions
    static const int SHADER_LOAD_LIGHT;
    static const int SHADER_LOAD_CLIP;
    static const int SHADER_BIND_TEX_NORM;

    // Constructor
    BasicShader(const char* vertexFile, const char* fragmentFile, int _mode);

    // Load transformation matrix into shader program
    void loadTransMatrix(const float* matrix);

    // Load camera matrix into shader program
    void loadCameraMatrix(const float* matrix);

    // Load projection matrix into shader program
    void loadProjMatrix(const float* matrix);

    // Load light into shader program
    void loadLight(Light* light);

    // Load sky color into shader program
    void loadSkyCol(float r, float g, float b);

    // Load clipping plane info into shader program
    void loadClipping(float height, bool clipPositive);

protected:

    // Get all uniform locations
    void getAllUniformLocs() override;

    // Bind VAO attributes
    void bindAttributes() override;

private:

    // Shader mode
    int mode;

    // Location of transformation matrix in shader program
    GLuint transMatrixLoc;

    // Location of camera matrix in the shader program
    GLuint cameraMatrixLoc;

    // Location of projection matrix in shader program
    GLuint projMatrixLoc;

    // Location of light position in shader program
    GLuint lightPosLoc;

    // Location of light color in shader program
    GLuint lightColLoc;

    // Location of sky color in shader program
    GLuint skyColLoc;

    // Location of clipping plane height in shader program
    GLuint clipHeightLoc;

    // Location of clipPositive in shader program
    GLuint clipPositiveLoc;
};

#endif
