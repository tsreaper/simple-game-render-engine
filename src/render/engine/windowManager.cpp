#include <cstdlib>
#include <iostream>
#include "../entities/camera.h"
#include "windowManager.h"

using namespace std;

// Window width
const int WindowManager::WINDOW_WIDTH = 1280;

// Window height
const int WindowManager::WINDOW_HEIGHT = 720;

// Window title
const char* WindowManager::WINDOW_TITLE = "OpenGL Game";

// Window pointer
GLFWwindow* WindowManager::window = NULL;

// Key pressed status
bool* WindowManager::keyPressed = new bool[500]();

// Check if a key is pressed
bool WindowManager::isKeyPressed(int key)
{
    return keyPressed[key];
}

// Create window
void WindowManager::createDisplay()
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
    
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    
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
    glEnable(GL_CLIP_DISTANCE0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

// Refresh window
void WindowManager::updateDisplay()
{
    glfwSwapBuffers(window);
	glfwPollEvents();
}

// Close window
void WindowManager::destroyDisplay()
{
    delete[] keyPressed;
    glfwDestroyWindow(window);
    glfwTerminate();
}

// Check if the window should close
bool WindowManager::isExiting()
{
    return glfwWindowShouldClose(window);
}

// Keyboard callback
void WindowManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        keyPressed[key] = true;
    else if (action == GLFW_RELEASE)
        keyPressed[key] = false;
}

// Error callback
void WindowManager::errorCallback(int error, const char* description)
{
    cerr << "ERROR: " << description << endl;
}
