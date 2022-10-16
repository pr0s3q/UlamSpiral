#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "CustomOpenGL.h"
#include <iostream>
#include <format>

#pragma region Constructors

CustomOpenGL::CustomOpenGL()
    : window(0)
{
    InitOpenGL(640, 480, "Window");
}

CustomOpenGL::CustomOpenGL(int width, int height, const char* title)
    : window(0)
{
    InitOpenGL(width, height, title);
}

CustomOpenGL::~CustomOpenGL()
{
}

#pragma endregion

#pragma region Public Methods

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

void CustomOpenGL::Loop()
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Render sample triangle */
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

void CustomOpenGL::SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{

    const std::string r = std::to_string(red / 255.0f);
    const std::string g = std::to_string(green / 255.0f);
    const std::string b = std::to_string(blue / 255.0f);
    const std::string a = std::to_string(alpha / 255.0f);

    std::string vertexShader =
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    std::string fragmentShader = 
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   color = vec4(" + r + ", " + g + ", " + b + ", " + a + ");\n"
        "}\n";

    CreateShader(vertexShader, fragmentShader, shader);

    glUseProgram(shader);
}

bool CustomOpenGL::ShouldTerminate()
{
    return glfwWindowShouldClose(window);
}

void CustomOpenGL::Terminate()
{
    glDeleteProgram(shader);
    glfwTerminate();
}

#pragma endregion

#pragma region Private Methods

unsigned int CustomOpenGL::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        SetOutcome((std::string)("Failed to compile " + (std::string)(type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader! \n" + message));
        glDeleteShader(id);
        return 0;
    }

    return id;
}

void CustomOpenGL::CreateShader(const std::string& vertexShader, const std::string& fragmentShader, unsigned int& shader)
{
    shader = glCreateProgram();
    unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(shader, vertex);
    glAttachShader(shader, fragment);
    glLinkProgram(shader);
    glValidateProgram(shader);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void CustomOpenGL::InitOpenGL(int width, int height, const char* title)
{
    if (!glfwInit())
    {
        SetOutcome("Cannot initialize GLFW");
        return;
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        SetOutcome("Cannot create window");
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        SetOutcome("Cannot initialize GLEW");
        return;
    }
}

void CustomOpenGL::SetOutcome(std::string errorMessage)
{
    throw std::runtime_error(errorMessage.c_str());
}

#pragma endregion