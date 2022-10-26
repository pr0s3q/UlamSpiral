#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "CustomOpenGL.h"
#include "Mathematic.h"
#include "UlamHelper.h"
#include "UlamOperationType.h"

#include <iostream>
#include <format>
#include <vector>

#pragma region Constructors

//---------------------------------------------------------------

CustomOpenGL::CustomOpenGL()
    : window(0)
{
    InitOpenGL(640, 480, "Window");
}

//---------------------------------------------------------------

CustomOpenGL::CustomOpenGL(
    int width,
    int height,
    const char* title)
    : window(0)
{
    InitOpenGL(width, height, title);
}

//---------------------------------------------------------------

CustomOpenGL::~CustomOpenGL()
{
}

//---------------------------------------------------------------

#pragma endregion

#pragma region Public Methods

//---------------------------------------------------------------

void CustomOpenGL::DrawBasicTriangle()
{
    elementsCount = 3;
    objectType = GL_TRIANGLES;

    double positions[6] =
    {
        -0.5 * scaleFactorX, -0.5 * scaleFactorY,
         0.0 * scaleFactorX,  0.5 * scaleFactorY,
         0.5 * scaleFactorX, -0.5 * scaleFactorY
    };

    unsigned int indicies[] =
    {
        0, 1, 2
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(elementsCount * 2) * sizeof(double), &positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(double) * 2, 0);

    unsigned int indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long>(elementsCount * 2) * sizeof(unsigned int), indicies, GL_STATIC_DRAW);
}

//---------------------------------------------------------------

void CustomOpenGL::DrawBasicSquare()
{
    elementsCount = 6;
    objectType = GL_TRIANGLES;

    double positions[] =
    {
        -0.5 * scaleFactorX, -0.5 * scaleFactorY, // 0
         0.5 * scaleFactorX, -0.5 * scaleFactorY, // 1
         0.5 * scaleFactorX,  0.5 * scaleFactorY, // 2
        -0.5 * scaleFactorX,  0.5 * scaleFactorY  // 3
    };

    unsigned int indicies[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(elementsCount * 2) * sizeof(double), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(double) * 2, 0);

    unsigned int indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsCount * sizeof(unsigned int), indicies, GL_STATIC_DRAW);
}

//---------------------------------------------------------------

void CustomOpenGL::DrawUlamSpiral(unsigned int maxNumber)
{
    UlamOperationType type = UlamOperationType::addX;
    std::vector<double> positions;
    unsigned int primeAmount = 0, amount = 0, stepsLeft = 1, rotationLeft = 2, steps = 1, currentNumber = 1;
    double precision = 0.0, posX = 0.0, posY = 0.0, distance = 0.0;
    bool scale = true;

    Mathematic::PrimeAmount(maxNumber, primeAmount);
    UlamHelper::GetPrecision(maxNumber, precision);

    if (maxNumber <= 39601)
    {
        distance = precision * 3 / 10;
        amount = primeAmount * 8;
        elementsCount = primeAmount * 6;
        objectType = GL_TRIANGLES;
    }
    else
    {
        scale = false;
        amount = primeAmount * 2;
        elementsCount = primeAmount;
        objectType = GL_POINTS;
    }

    positions.reserve(amount);

    while (positions.size() != amount && posX < 1 && posY < 1 && posX > -1 && posY > -1)
    {
        while (rotationLeft != 0)
        {
            stepsLeft = steps;
            while (stepsLeft != 0)
            {
                switch (type)
                {
                case UlamOperationType::addX:
                    posX += precision;
                    break;

                case UlamOperationType::addY:
                    posY += precision;
                    break;

                case UlamOperationType::removeX:
                    posX -= precision;
                    break;

                case UlamOperationType::removeY:
                    posY -= precision;
                    break;
                }
                if (posX >= 1 || posY >= 1 || posX <= -1 || posY <= -1)
                    break;
                posX = round(posX * 1000000) / 1000000;
                posY = round(posY * 1000000) / 1000000;
                if (Mathematic::IsPrime(currentNumber))
                {
                    if (scale)
                    {
                        positions.emplace_back((posX - distance) * scaleFactorX);
                        positions.emplace_back((posY - distance) * scaleFactorY);

                        positions.emplace_back((posX + distance) * scaleFactorX);
                        positions.emplace_back((posY - distance) * scaleFactorY);

                        positions.emplace_back((posX + distance) * scaleFactorX);
                        positions.emplace_back((posY + distance) * scaleFactorY);

                        positions.emplace_back((posX - distance) * scaleFactorX);
                        positions.emplace_back((posY + distance) * scaleFactorY);
                    }
                    else
                    {
                        positions.emplace_back(posX * scaleFactorX);
                        positions.emplace_back(posY * scaleFactorY);
                    }
                }
                currentNumber++;
                stepsLeft--;
            }
            if (posX >= 1 || posY >= 1 || posX <= -1 || posY <= -1)
                break;
            rotationLeft--;
            switch (type)
            {
            case UlamOperationType::addX:
                type = UlamOperationType::addY;
                break;

            case UlamOperationType::addY:
                type = UlamOperationType::removeX;
                break;

            case UlamOperationType::removeX:
                type = UlamOperationType::removeY;
                break;

            case UlamOperationType::removeY:
                type = UlamOperationType::addX;
                break;
            }

        }
        rotationLeft = 2;
        steps++;
    }

    std::vector<unsigned int> indicies;
    indicies.reserve(elementsCount);

    if (scale)
    {
        for (int i = 0; i < primeAmount; i++)
        {
            indicies.emplace_back(i * 4 + 0);
            indicies.emplace_back(i * 4 + 1);
            indicies.emplace_back(i * 4 + 2);
            indicies.emplace_back(i * 4 + 2);
            indicies.emplace_back(i * 4 + 3);
            indicies.emplace_back(i * 4 + 0);
        }
    }
    else
    {
        for (int i = 0; i < amount; i++)
            indicies.emplace_back(i);
    }

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, (unsigned long long)(amount) * sizeof(double), &positions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(double) * 2, 0);

    unsigned int indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsCount * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);
}

//---------------------------------------------------------------

void CustomOpenGL::Loop()
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Render sample triangle */
    glDrawElements(objectType, elementsCount, GL_UNSIGNED_INT, nullptr);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

//---------------------------------------------------------------

void CustomOpenGL::SetColor(
    unsigned char red,
    unsigned char green,
    unsigned char blue,
    unsigned char alpha)
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

//---------------------------------------------------------------

bool CustomOpenGL::ShouldTerminate()
{
    return glfwWindowShouldClose(window);
}

//---------------------------------------------------------------

void CustomOpenGL::Terminate()
{
    glDeleteProgram(shader);
    glfwTerminate();
}

//---------------------------------------------------------------

#pragma endregion

#pragma region Private Methods

//---------------------------------------------------------------

unsigned int CustomOpenGL::CompileShader(
    unsigned int type,
    const std::string& source)
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
        SetOutcome((std::string)("Failed to compile "
            + (std::string)(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            + " shader! \n" + message));
        glDeleteShader(id);
        return 0;
    }

    return id;
}

//---------------------------------------------------------------

void CustomOpenGL::CreateShader(
    const std::string& vertexShader,
    const std::string& fragmentShader,
    unsigned int& shader)
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

//---------------------------------------------------------------

void CustomOpenGL::InitOpenGL(
    int width,
    int height,
    const char* title)
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

    scaleFactorX = 1000.0 / width;
    scaleFactorY = 1000.0 / height;
}

//---------------------------------------------------------------

void CustomOpenGL::SetOutcome(std::string errorMessage)
{
    throw std::runtime_error(errorMessage.c_str());
}

//---------------------------------------------------------------

#pragma endregion
