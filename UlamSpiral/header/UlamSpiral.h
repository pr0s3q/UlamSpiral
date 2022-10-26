#pragma once

#include "CustomOpenGL.h"

/// <summary>
/// Ulam Spiral class. Responsible for whole program logic
/// </summary>
class UlamSpiral
{
public:

    //---------------------------------------------------------------

    /// <summary>
    /// Run the UlamSpiral program.
    /// </summary>
    /// <returns>-1 if something went wrong. Otherwise 0</returns>
    static int Run();

    //---------------------------------------------------------------

private:

    //---------------------------------------------------------------

    /// <summary>
    /// Default constructor. Create 640x480 window with "Window" title.
    /// Consider using overloaded constructor for custom sized window with custom title
    /// </summary>
    UlamSpiral();

    //---------------------------------------------------------------

    /// <summary>
    /// Basic constructor. Initialize CustomOpenGL class
    /// </summary>
    /// <param name="width">Width of the Ulam's Spiral app</param>
    /// <param name="height">Height of the Ulam's Spiral app</param>
    /// <param name="title">Title of the Ulam's Spiral app which is shown on titlebar/navbar</param>
    UlamSpiral(
        int width,
        int height,
        const char* title);

    //---------------------------------------------------------------

    ~UlamSpiral();

    //---------------------------------------------------------------

    /// <summary>
    /// Initialize UlamSpiral class
    /// </summary>
    void Init();

    //---------------------------------------------------------------

    /// <summary>
    /// Main loop of the app
    /// </summary>
    void Loop();

    //---------------------------------------------------------------

    static const int width = 1800;
    static const int height = 1000;
    static inline const char* title = "Ulam Spiral";

    CustomOpenGL openGL;

    //---------------------------------------------------------------
};


