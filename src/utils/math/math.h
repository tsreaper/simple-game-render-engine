#ifndef MATH_H_
#define MATH_H_

// Math helper class
class Math
{
public:

    // Normalize a vector
    static void normalize(float* vec, int d);

    // Create a 4x4 transformation matrix
    static float* createTransMatrix(float tX, float tY, float tZ, float rX, float rY, float rZ, float scale, bool isCamera = false);

    // Create a 4x4 projection matrix
    static float* createProjMatrix(float ratio, float fov, float zNear, float zFar);

    // Create a 4x4 orthogonal projection matrix
    static float* createOrthoMatrix(float ratio, float hov, float zNear, float zFar);

private:

    // Calculate A = B*A, where A and B are both 4x4 matrices
    static void leftMulMatrix4(float* A, float* B);

    // Calculate rotation matrix
    static void calcRotationMatrix(float* res, float rX, float rY, float rZ);

    // Calculate translation matrix
    static void calcTranslationMatrix(float* res, float tX, float tY, float tZ);
};

#endif
