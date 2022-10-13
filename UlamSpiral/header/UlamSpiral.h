#pragma once

#include "CustomOpenGL.h"

/// <summary>
/// Ulam Spiral class. Responsible for whole program logic
/// </summary>
class UlamSpiral
{
public:

    /// <summary>
    /// Default constructor. Create 640x480 window with "Window" title.
    /// Consider using overloaded constructor for custom sized window with custom title
    /// </summary>
    UlamSpiral();

    /// <summary>
    /// Basic constructor. Initialize CustomOpenGL class
    /// </summary>
    /// <param name="width">Width of the Ulam's Spiral app</param>
    /// <param name="height">Height of the Ulam's Spiral app</param>
    /// <param name="title">Title of the Ulam's Spiral app which is shown on titlebar/navbar</param>
    UlamSpiral(int width, int height, const char* title);

    ~UlamSpiral();

    /// <summary>
    /// Returns error message
    /// </summary>
    /// <returns></returns>
    std::string* GetErrorMessage();

    /// <summary>
    /// Initialize UlamSpiral class
    /// </summary>
    void Init();

    /// <summary>
    /// Check if CustomOpenGL does not have any errors
    /// </summary>
    /// <returns></returns>
    bool IsValid();

    /// <summary>
    /// Main loop of the app
    /// </summary>
    void Loop();

private:
    CustomOpenGL m_openGL;
};


