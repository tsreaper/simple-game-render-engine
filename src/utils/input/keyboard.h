#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "../../glew.h"
#include <GLFW/glfw3.h>

// Keyboard input
class Keyboard
{
public:

    // Check if a key is pressed
    static bool isKeyPressed(int key);

    // Key callback
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

    // Key pressed status
    static bool keyPressed[500];
};

#endif
