#ifndef MATH_H_
#define MATH_H_

#include "utils/struct/struct.h"

// Math helper class
class Math
{
public:

    // Calculate the distance between two 3D points
    static float distance(vec3 a, vec3 b);

    // Normalize a 3D vector
    static void normalize(vec3 v);

    // Create a 4x4 transformation matrix
    static float* createTransMatrix(vec3 pos, vec3 rot, float scale, bool isCamera = false);

    // Create a 4x4 projection matrix
    static float* createProjMatrix(float ratio, float fov, float zNear, float zFar);

    // Create a 4x4 orthogonal projection matrix
    static float* createOrthoMatrix(float ratio, float hov, float zNear, float zFar);

private:

    // Calculate A = B*A, where A and B are both 4x4 matrices
    static void leftMulMatrix4(float* A, float* B);

    // Calculate rotation matrix
    static void calcRotationMatrix(float* res, vec3 rot, const char* order = "xyz");

    // Calculate translation matrix
    static void calcTranslationMatrix(float* res, vec3 pos);
};

#endif
