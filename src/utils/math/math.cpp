#include <cmath>
#include "utils/math/math.h"

// Calculate the distance between two 3D points
float Math::distance(vec3 a, vec3 b)
{
    return sqrt(
        (a.x - b.x) * (a.x - b.x) +
        (a.y - b.y) * (a.y - b.y) +
        (a.z - b.z) * (a.z - b.z)
    );
}

// Normalize a 3D vector
void Math::normalize(vec3 v)
{
    float len = distance(v, vec3(0, 0, 0));
    v.x /= len;
    v.y /= len;
    v.z /= len;
}

// Create a 4x4 transformation matrix
float* Math::createTransMatrix(vec3 pos, vec3 rot, float scale, bool isCamera)
{
    // Initialize a 4x4 identity matrix;
    float* res = new float[4*4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res[i*4+j] = (i == j);

    // Scaling
    float* scalingMatrix = new float[4*4] {
        scale, 0, 0, 0,
        0, scale, 0, 0,
        0, 0, scale, 0,
        0, 0, 0, 1
    };
    leftMulMatrix4(res, scalingMatrix);
    delete[] scalingMatrix;

    if (isCamera)
    {
        calcTranslationMatrix(res, pos);
        calcRotationMatrix(res, rot, "zyx");
    }
    else
    {
        calcRotationMatrix(res, rot);
        calcTranslationMatrix(res, pos);
    }

    return res;
}

// Create a 4x4 projection matrix
float* Math::createProjMatrix(float ratio, float fov, float zNear, float zFar)
{
    return new float[4*4] {
        1/(float)tan(fov/2)/ratio, 0, 0, 0,
        0, 1/(float)tan(fov/2), 0, 0,
        0, 0, -(zFar+zNear)/(zFar-zNear), -1,
        0, 0, -2*zFar*zNear/(zFar-zNear), 0
    };
}

// Create a 4x4 orthogonal projection matrix
float* Math::createOrthoMatrix(float ratio, float hov, float zNear, float zFar)
{
    return new float[4*4] {
        1/hov/ratio, 0, 0, 0,
        0, 1/hov, 0, 0,
        0, 0, 1/(zNear-zFar), 0,
        0, 0, zNear/(zNear-zFar), 1
    };
}

// Calculate A = B*A, where A and B are both 4x4 matrices
void Math::leftMulMatrix4(float* A, float* B)
{
    float res[16] = {0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                res[j*4+i] += B[k*4+i] * A[j*4+k];
    for (int i = 0; i < 16; i++)
        A[i] = res[i];
}

// Calculate rotation matrix
void Math::calcRotationMatrix(float* res, vec3 rot, const char* order)
{
    for (int i = 0; i < 3; i++)
    {
        if (order[i] == 'x')
        {
            // Pitch
            float* rotateXMatrix = new float[4*4] {
                1, 0, 0, 0,
                0, (float)cos(rot.x), (float)sin(rot.x), 0,
                0, (float)-sin(rot.x), (float)cos(rot.x), 0,
                0, 0, 0, 1
            };
            leftMulMatrix4(res, rotateXMatrix);
            delete[] rotateXMatrix;
        }
        else if (order[i] == 'y')
        {
            // Yaw
            float* rotateYMatrix = new float[4*4] {
                (float)cos(rot.y), 0, (float)-sin(rot.y), 0,
                0, 1, 0, 0,
                (float)sin(rot.y), 0, (float)cos(rot.y), 0,
                0, 0, 0, 1
            };
            leftMulMatrix4(res, rotateYMatrix);
            delete[] rotateYMatrix;
        }
        else
        {
            // Roll
            float* rotateZMatrix = new float[4*4] {
                (float)cos(rot.z), (float)sin(rot.z), 0, 0,
                (float)-sin(rot.z), (float)cos(rot.z), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
            leftMulMatrix4(res, rotateZMatrix);
            delete[] rotateZMatrix;
        }
    }
}

// Calculate translation matrix
void Math::calcTranslationMatrix(float* res, vec3 pos)
{
    // Translation
    float* translationMatrix = new float[4*4] {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        pos.x, pos.y, pos.z, 1
    };
    leftMulMatrix4(res, translationMatrix);
    delete[] translationMatrix;
}
