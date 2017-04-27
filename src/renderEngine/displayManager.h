#ifndef DISPLAY_MANAGER_H_
#define DISPLAY_MANAGER_H_

#include <GLFW/glfw3.h>

class DisplayManager
{
    public:
    
    static int DISPLAY_WIDTH;
    static int DISPLAY_HEIGHT;
    static char* DISPLAY_TITLE;
    
    static void createDisplay();
    static void updateDisplay();
    static void destroyDisplay();
    static bool isExiting();
    
    private:
    
    static GLFWwindow* window;
    
    static void errorCallback(int error, const char* description);
};

#endif
