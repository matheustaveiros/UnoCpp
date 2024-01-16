#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Enums.h"

class ConsoleHelper
{
private:
    static Enums::DisplayLevel _displayLevel;

public:
    
    static void PrintMessage(const std::string& message, Enums::DisplayLevel displayLevel = Enums::DisplayLevel::Player);
    static void PrintMessage(const std::vector<std::string>& lines, Enums::DisplayLevel displayLevel = Enums::DisplayLevel::Player);
    static void Clear();
    static void SetDisplayLevel(Enums::DisplayLevel displayLevel);

    template<typename T>
    static T GetInput(std::string_view message);

    static void WaitForAnyKey(std::string message);
};

template <typename T>
T ConsoleHelper::GetInput(std::string_view message)
{
    T input{};
    std::cout << message;
    std::cin >> std::ws >> input;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        return GetInput<T>(message);
    }
    return input;
}