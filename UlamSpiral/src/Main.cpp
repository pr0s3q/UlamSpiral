#include <iostream>

#include "UlamSpiral.h"

int width = 640;
int height = 480;
const char* title = "Ulam Spiral";

int main(void)
{
    UlamSpiral ulamSpiral(width, height, title);

    if(!ulamSpiral.IsValid())
    {
        std::string* message = ulamSpiral.GetErrorMessage();
        std::cout << *message << std::endl;
        return -1;
    }

    ulamSpiral.Init();

    ulamSpiral.Loop();

    return 0;
}