#ifndef DISPLAY_MANAGER_H_
#define DISPLAY_MANAGER_H_

#include <GLFW/glfw3.h>

// Class for displaying window
class DisplayManager
{
public:
    
    // Window width
    static const int DISPLAY_WIDTH;
    
    // Window height
    static const int DISPLAY_HEIGHT;
    
    // Window title
    static const char* DISPLAY_TITLE;
    
    // Check if a key is pressed
    static bool isKeyPressed(int key);
    
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
    
    // Key pressed status
    static bool* keyPressed;
    
    // Key callback
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    // Error callback
    static void errorCallback(int error, const char* description);
};

#endif
