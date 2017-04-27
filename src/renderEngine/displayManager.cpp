#include <cstdlib>
#include <iostream>
#include "../glew.h"
#include "displayManager.h"

using namespace std;

int DisplayManager::DISPLAY_WIDTH = 1280;
int DisplayManager::DISPLAY_HEIGHT = 720;
char* DisplayManager::DISPLAY_TITLE = "OpenGL Game";
GLFWwindow* DisplayManager::window = NULL;

void DisplayManager::createDisplay()
{
    // Init GLFW
    if (!glfwInit())
    {
        cerr << "ERROR: Could not start GLFW3!" << endl;
        exit(-1);
    }
    
    // Set the window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
    
    window = glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_TITLE, NULL, NULL);
    
    // Check if the window is created
    if (window == NULL)
    {
        cerr << "ERROR: Could not create window!" << endl;
        glfwTerminate();
        exit(-1);
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);
    
    // Init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
		cerr << "ERROR: Could not start GLEW!" << endl;
        exit(-1);
	}
}

void DisplayManager::updateDisplay()
{
    glfwSwapBuffers(window);
	glfwPollEvents();
}

void DisplayManager::destroyDisplay()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool DisplayManager::isExiting()
{
    return glfwWindowShouldClose(window);
}
