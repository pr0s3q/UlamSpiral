#include "UlamSpiral.h"
#include "CustomOpenGL.h"
#include <iostream>

#pragma region Constructors

//---------------------------------------------------------------

UlamSpiral::UlamSpiral()
{
}

//---------------------------------------------------------------

UlamSpiral::UlamSpiral(
    int width,
    int height,
    const char* title)
    : openGL(width, height, title)
{

}

//---------------------------------------------------------------

UlamSpiral::~UlamSpiral()
{
    openGL.Terminate();
}

//---------------------------------------------------------------

#pragma endregion

#pragma Public Methods

//---------------------------------------------------------------

int UlamSpiral::Run()
{
    try
    {
        /*int width = 1400;
        int height = 1050;
        const char* title = "Ulam Spiral";*/

        UlamSpiral ulamSpiral(width, height, title);

        ulamSpiral.Init();

        ulamSpiral.Loop();

        return 0;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
}

//---------------------------------------------------------------

#pragma endregion

#pragma region Private Methods

//---------------------------------------------------------------

void UlamSpiral::Init()
{
    openGL.DrawBasicTriangle();
    openGL.SetColor(0, 150, 150, 255);
}

//---------------------------------------------------------------

void UlamSpiral::Loop()
{
    /* Loop until the user closes the window */
    while (!openGL.ShouldTerminate())
    {
        openGL.Loop();
    }
}

//---------------------------------------------------------------

#pragma endregion
