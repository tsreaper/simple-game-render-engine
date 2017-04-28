#ifndef MATH_H_
#define MATH_H_

// Math helper class
class Math
{
public:
    
    // Create a 4x4 transformation matrix
    static float* createTransMatrix(float tX, float tY, float tZ, float rX, float rY, float rZ, float scale);
    
    // Create a 4x4 projection matrix
    static float* createProjMatrix(float ratio, float fov, float zNear, float zFar);
    
private:
    
    // Calculate A = B*A, where A and B are both 4x4 matrices
    static void leftMulMatrix4(float* A, float* B);
};

#endif
