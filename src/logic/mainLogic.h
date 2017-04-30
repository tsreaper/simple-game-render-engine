#ifndef MAIN_LOGIC_H_
#define MAIN_LOGIC_H_

#include "../glew.h"
#include <GLFW/glfw3.h>

// Main logic of game
class MainLogic
{
public:
    
    // Initialize main logic
    static void init();
    
    // Run main logic
    static void run();
    
    // Clean up
    static void cleanUp();
};

#endif
