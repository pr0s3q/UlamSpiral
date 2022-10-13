#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "CustomOpenGL.h"

CustomOpenGL::CustomOpenGL()
    : m_isValid(true), m_errorMessage(), m_window(0)
{
    m_isValid = InitOpenGL(640, 480, "Window");
}

CustomOpenGL::CustomOpenGL(int width, int height, const char* title)
    : m_isValid(true), m_errorMessage(), m_window(0)
{
    m_isValid = InitOpenGL(width, height, title);
}

CustomOpenGL::~CustomOpenGL()
{
}

void CustomOpenGL::DrawBasicTriangle()
{
    float positions[6] =
    {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
}

std::string* CustomOpenGL::GetErrorMessage()
{
    return &m_errorMessage;
}

bool CustomOpenGL::InitOpenGL(int width, int height, const char* title)
{
    if (!glfwInit())
    {
        m_errorMessage = "Cannot initialize GLFW";
        return false;
    }

    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!m_window)
    {
        m_errorMessage = "Cannot create window";
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    if (glewInit() != GLEW_OK)
    {
        m_errorMessage = "Cannot initialize GLEW";
        return false;
    }

    return true;
}

bool CustomOpenGL::IsValid()
{
    return m_isValid;
}

void CustomOpenGL::Loop()
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Render sample triangle */
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);

    /* Poll for and process events */
    glfwPollEvents();
}

bool CustomOpenGL::ShouldTerminate()
{
    return glfwWindowShouldClose(m_window);
}

void CustomOpenGL::Terminate()
{
    glfwTerminate();
}
