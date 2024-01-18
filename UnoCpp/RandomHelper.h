#pragma once
#include <iostream>
#include <chrono>
#include <random>

class RandomHelper
{
public:
    static std::mt19937 Generator;
    static void Seed();
    static int Range(int min, int max);
};