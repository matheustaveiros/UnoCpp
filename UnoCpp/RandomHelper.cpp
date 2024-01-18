#include "RandomHelper.h"

std::mt19937 RandomHelper::Generator;

void RandomHelper::Seed()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator.seed(seed);
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

    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(Generator);
}