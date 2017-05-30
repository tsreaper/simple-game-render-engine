#ifndef _MAIN_LOGIC_H
#define _MAIN_LOGIC_H

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
