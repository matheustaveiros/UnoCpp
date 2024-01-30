#pragma once
#include <iostream>
#include <chrono>
#include <random>

class RandomHelper
{
public:
    static std::mt19937 Generator;
    static void Seed();

    template<typename T>
    static T Range(T min, T max);
};

template <typename T>
T RandomHelper::Range(T min, T max)
{
    if (min > max)
    {
        std::cerr << "Error: Invalid range in Random::Range function." << std::endl;
        return 0;
    }

    std::uniform_int_distribution<T> distribution(min, max);
    return distribution(Generator);
}