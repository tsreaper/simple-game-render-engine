#include <cstdlib>
#include <iostream>
#include "../../glew.h"
#include "../entities/camera.h"
#include "displayManager.h"

using namespace std;

// Window width
const int DisplayManager::DISPLAY_WIDTH = 1280;

// Window height
const int DisplayManager::DISPLAY_HEIGHT = 720;

// Window title
const char* DisplayManager::DISPLAY_TITLE = "OpenGL Game";

// Window pointer
GLFWwindow* DisplayManager::window = NULL;

// Key pressed status
bool* DisplayManager::keyPressed = new bool[500]();

// Check if a key is pressed
bool DisplayManager::isKeyPressed(int key)
{
    return keyPressed[key];
}

// Create window
void DisplayManager::createDisplay()
{
    // Set error callback
    glfwSetErrorCallback(errorCallback);
    
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
    
    // Set input callbacks
    glfwSetKeyCallback(window, keyCallback);
    
    // Show window
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
    
    glEnable(GL_DEPTH_TEST);
}

// Refresh window
void DisplayManager::updateDisplay()
{
    glfwSwapBuffers(window);
	glfwPollEvents();
}

// Close window
void DisplayManager::destroyDisplay()
{
    delete[] keyPressed;
    glfwDestroyWindow(window);
    glfwTerminate();
}

// Check if the window should close
bool DisplayManager::isExiting()
{
    return glfwWindowShouldClose(window);
}

// Keyboard callback
void DisplayManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        keyPressed[key] = true;
    else if (action == GLFW_RELEASE)
        keyPressed[key] = false;
}

// Error callback
void DisplayManager::errorCallback(int error, const char* description)
{
    cerr << "ERROR: " << description << endl;
}
