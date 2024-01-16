#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
class RandomHelper
{
public:
    static void Seed();
    static int Range(int min, int max);
};