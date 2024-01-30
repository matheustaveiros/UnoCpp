#include "RandomHelper.h"

std::mt19937 RandomHelper::Generator;

void RandomHelper::Seed()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    Generator.seed(seed);
}