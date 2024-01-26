// UnoCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Core/GameManager.h"
int main()
{
    auto gameManager = GameManager();

    return gameManager.EntryPoint();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu