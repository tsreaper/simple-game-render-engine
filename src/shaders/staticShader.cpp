#include "../glew.h"
#include "staticShader.h"

using namespace std;

char* StaticShader::VERTEX_FILE = "src/shaders/shaderSource/vertexShader.txt";
char* StaticShader::FRAGMENT_FILE = "src/shaders/shaderSource/fragmentShader.txt";

StaticShader::StaticShader(): ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
    bindAttributes();
    glLinkProgram(programId);
    glValidateProgram(programId);
}

void StaticShader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
}
