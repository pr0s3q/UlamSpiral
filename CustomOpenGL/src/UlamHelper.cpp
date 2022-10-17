#include "UlamHelper.h"

//---------------------------------------------------------------

void UlamHelper::GetPrecision(unsigned int number, double& precision)
{
    if (number > 3996001)
        return;

    for (int i = 0; i < arraysSize; i++)
    {
        if (number > maxElements[i])
            continue;

        precision = precisions[i];
        return;
    }

}

//---------------------------------------------------------------
