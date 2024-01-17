#include "RandomHelper.h"
void RandomHelper::Seed()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

/// <summary>
/// Generates a Random number between min and max (Inclusively)
/// </summary>
/// <param name="min">Inclusive</param>
/// <param name="max">Inclusive</param>
/// <returns></returns>
int RandomHelper::Range(int min, int max)
{
    if (min > max)
    {
        std::cerr << "Error: Invalid range in Random::Range function." << std::endl;
        return 0;
    }

    int rangeSize = max - min + 1;

    return min + (rand() % rangeSize);
}