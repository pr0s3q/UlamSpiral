#pragma once

#include "GLFW/glfw3.h"

#include <string>

/// <summary>
/// Custom OpenGL class. Contains glfw3 and glew library. Create for simplicity purpose
/// If something will went wrong, std::runtime_error exception will be thrown with propper error message
/// </summary>
class CustomOpenGL
{
public:

    //---------------------------------------------------------------

    /// <summary>
    /// Default constructor.Create 640x480 window with "Window" title.
    /// Consider using overloaded constructor for custom sized window with custom title
    /// </summary>
    CustomOpenGL();

    //---------------------------------------------------------------

    /// <summary>
    /// Basic constructor. 
    /// </summary>
    /// <param name="width">Width of the app window</param>
    /// <param name="height">Height of the app window</param>
    /// <param name="title">Title of the app window which is shown on titlebar/navbar</param>
    CustomOpenGL(
        int width,
        int height,
        const char* title);

    //---------------------------------------------------------------

    ~CustomOpenGL();

    //---------------------------------------------------------------

    /// <summary>
    /// Draw basic triangle
    /// </summary>
    void DrawBasicTriangle();

    //---------------------------------------------------------------

    /// <summary>
    /// Main loop
    /// </summary>
    void Loop();

    //---------------------------------------------------------------

    /// <summary>
    /// Set color of previously drawn entity
    /// </summary>
    /// <param name="red">Red color saturation (0 - 255)</param>
    /// <param name="green">Green color saturation (0 - 255)</param>
    /// <param name="blue">Blue color saturation (0 - 255)</param>
    /// <param name="alpha">Color opacity (0 -255)</param>
    void SetColor(
        unsigned char red,
        unsigned char green,
        unsigned char blue,
        unsigned char alpha);

    //---------------------------------------------------------------

    /// <summary>
    /// Check if app should terminated.
    /// </summary>
    /// <returns>True if user closes the window. False otherwise</returns>
    bool ShouldTerminate();

    //---------------------------------------------------------------

    /// <summary>
    /// Terminate OpenGL library and close all windows and free alocated memory.
    /// Call, before exit the application
    /// </summary>
    void Terminate();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    /// <summary>
    /// 
    /// </summary>
    /// <param name="type"></param>
    /// <param name="source"></param>
    /// <returns></returns>
    unsigned int CompileShader(
        unsigned int type,
        const std::string& source);

    //---------------------------------------------------------------

    /// <summary>
    /// 
    /// </summary>
    /// <param name="vertexShader"></param>
    /// <param name="fragmentShader"></param>
    /// <param name="shader"></param>
    void CreateShader(
        const std::string& vertexShader,
        const std::string& fragmentShader,
        unsigned int& shader);

    //---------------------------------------------------------------

    /// <summary>
    /// Initialize OpenGL library - glfw and glaw
    /// </summary>
    /// <param name="width">Width of the app window</param>
    /// <param name="height">Height of the app window</param>
    /// <param name="title">Title of the app window which is shown on titlebar/navbar</param>
    /// <returns>True, if initialized successfully. False otherwise</returns>
    void InitOpenGL(
        int width,
        int height,
        const char* title);

    //---------------------------------------------------------------

    /// <summary>
    /// Set outcome if something went wrong. Throw std::runtime_error exception
    /// </summary>
    /// <param name="errorMessage">Outcome error message</param>
    void SetOutcome(std::string errorMessage);

    //---------------------------------------------------------------

    unsigned int shader;
    GLFWwindow* window;

    //---------------------------------------------------------------
};