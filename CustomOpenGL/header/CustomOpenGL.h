#pragma once

#include "GLFW/glfw3.h"

#include <string>

/// <summary>
/// Custom OpenGL class. Contains glfw3 and glew library. Create for simplicity purpose
/// </summary>
class CustomOpenGL
{
public:

    /// <summary>
    /// Default constructor.Create 640x480 window with "Window" title.
    /// Consider using overloaded constructor for custom sized window with custom title
    /// </summary>
    CustomOpenGL();

    /// <summary>
    /// Basic constructor. 
    /// </summary>
    /// <param name="width">Width of the app window</param>
    /// <param name="height">Height of the app window</param>
    /// <param name="title">Title of the app window which is shown on titlebar/navbar</param>
    CustomOpenGL(int width, int height, const char* title);

    ~CustomOpenGL();

    /// <summary>
    /// Draw basic triangle
    /// </summary>
    void DrawBasicTriangle();

    /// <summary>
    /// Returns error message
    /// </summary>
    /// <returns></returns>
    std::string* GetErrorMessage();

    /// <summary>
    /// Check if library does not have any errors
    /// </summary>
    /// <returns></returns>
    bool IsValid();

    /// <summary>
    /// Main loop
    /// </summary>
    void Loop();

    /// <summary>
    /// Check if app should terminated.
    /// </summary>
    /// <returns>True if user closes the window. False otherwise</returns>
    bool ShouldTerminate();

    /// <summary>
    /// Terminate OpenGL library and close all windows and free alocated memory.
    /// Call, before exit the application
    /// </summary>
    void Terminate();

private:

    /// <summary>
    /// Initialize OpenGL library - glfw and glaw
    /// </summary>
    /// <param name="width">Width of the app window</param>
    /// <param name="height">Height of the app window</param>
    /// <param name="title">Title of the app window which is shown on titlebar/navbar</param>
    /// <returns>True, if initialized successfully. False otherwise</returns>
    bool InitOpenGL(int width, int height, const char* title);

    bool m_isValid;
    std::string m_errorMessage;
    GLFWwindow* m_window;
};