#ifndef STATIC_PROGRAM_H_
#define STATIC_PROGRAM_H_

using namespace std;

class ShaderProgram
{
    public:
    
    ShaderProgram(char* vertexFile, char* fragmentFile);
    void start();
    void stop();
    void cleanUp();
    
    protected:
    
    int programId;
    
    void bindAttributes();
    void bindAttribute(int attr, char* varName);
    
    private:
    
    int vertexShaderId;
    int fragmentShaderId;
    
    static int loadShader(char* filename, int type);
};

#endif
