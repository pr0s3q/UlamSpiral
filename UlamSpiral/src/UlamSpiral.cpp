#include "UlamSpiral.h"
#include "CustomOpenGL.h"


UlamSpiral::UlamSpiral()
{
}

UlamSpiral::UlamSpiral(int width, int height, const char* title)
    : m_openGL(width, height, title)
{

}

UlamSpiral::~UlamSpiral()
{

}

std::string* UlamSpiral::GetErrorMessage()
{
    return m_openGL.GetErrorMessage();
}

void UlamSpiral::Init()
{
    m_openGL.DrawBasicTriangle();
}

bool UlamSpiral::IsValid()
{
    return m_openGL.IsValid();
}

void UlamSpiral::Loop()
{
    /* Loop until the user closes the window */
    while (!m_openGL.ShouldTerminate())
    {
        m_openGL.Loop();
    }

    m_openGL.Terminate();
}
