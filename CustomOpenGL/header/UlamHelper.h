#include <map>

class UlamHelper
{
public:

    /// <summary>
    /// Gen precision for drawing elements
    /// </summary>
    /// <param name="number"></param>
    /// <param name="precision"></param>
    static void GetPrecision(unsigned int number, double& precision);

private:

    static const unsigned char arraysSize = 9;

    static inline const unsigned int maxElements[] =
    {
        9, 81, 361, 1521, 9801, 39601, 159201, 998001, 3996001
    };

    static inline const double precisions[] =
    {
        0.5, 0.2, 0.1, 0.05, 0.02, 0.01, 0.005, 0.002, 0.001
    };
};