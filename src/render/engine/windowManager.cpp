#include <cstdlib>
#include <iostream>
#include <string>

#include "utils/input/keyboard.h"
#include "render/engine/windowManager.h"

using namespace std;

// Window width
const int WindowManager::WINDOW_WIDTH = 1280;

// Window height
const int WindowManager::WINDOW_HEIGHT = 720;

// Window title
const char* WindowManager::WINDOW_TITLE = "OpenGL Game";

// Window pointer
GLFWwindow* WindowManager::window = NULL;

// For calculating FPS
float WindowManager::lastTime = 0;
int WindowManager::renderedFrames = 0;

// Create window
void WindowManager::createDisplay()
{
    // Set error callback
    glfwSetErrorCallback(errorCallback);

    // Init GLFW
    if (!glfwInit())
    {
        cerr << "ERROR: [WindowManager::createDisplay] Could not start GLFW3!" << endl;
        exit(-1);
    }

    // Set the window
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    // Check if the window is created
    if (window == NULL)
    {
        cerr << "ERROR: [WindowManager::createDisplay] Could not create window!" << endl;
        glfwTerminate();
        exit(-1);
    }

    // Set input callbacks
    glfwSetKeyCallback(window, Keyboard::keyCallback);

    // Show window
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);

    // Init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
		cerr << "ERROR: [WindowManager::createDisplay] Could not start GLEW!" << endl;
        exit(-1);
	}

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CLIP_DISTANCE0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    glfwDestroyWindow(window);
    glfwTerminate();
}

// Check if the window should close
bool WindowManager::isExiting()
{
    return glfwWindowShouldClose(window);
}

// Show FPS on the window title
void WindowManager::updateFps()
{
    float currentTime = glfwGetTime();
    renderedFrames++;

    if (currentTime - lastTime >= 1)
    {
        glfwSetWindowTitle(window, (string(WINDOW_TITLE) + " - FPS: " + to_string(renderedFrames / (currentTime-lastTime))).c_str());
        lastTime = currentTime;
        renderedFrames = 0;
    }
}

// Error callback
void WindowManager::errorCallback(int error, const char* description)
{
    cerr << "ERROR: [WindowManager::errorCallback] " << error << " " << description << endl;
    exit(-1);
}
