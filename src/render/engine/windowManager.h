#ifndef _WINDOW_MANAGER_H
#define _WINDOW_MANAGER_H

#include "../../glew.h"
#include <GLFW/glfw3.h>

// Class for displaying window
class WindowManager
{
public:

    // Window width
    static const int WINDOW_WIDTH;

    // Window height
    static const int WINDOW_HEIGHT;

    // Window title
    static const char* WINDOW_TITLE;

    // Create window
    static void createDisplay();

    // Refresh window
    static void updateDisplay();

    // Close window
    static void destroyDisplay();

    // Check if window should close
    static bool isExiting();

private:

    // Window pointer
    static GLFWwindow* window;

    // Error callback
    static void errorCallback(int error, const char* description);
};

#endif
