#include "utils/input/keyboard.h"

// Key pressed status
bool Keyboard::keyPressed[500];

// Check if a key is pressed
bool Keyboard::isKeyPressed(int key)
{
    return keyPressed[key];
}

// Keyboard callback
void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        keyPressed[key] = true;
    else if (action == GLFW_RELEASE)
        keyPressed[key] = false;
}
