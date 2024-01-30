#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Utils/Enums.h"

class ConsoleHelper
{
private:
    static Enums::DisplayLevel _displayLevel;

public:
    
    static void PrintMessage(std::string_view, Enums::DisplayLevel displayLevel = Enums::DisplayLevel::Player);
    static void PrintMessage(const std::vector<std::string_view>& lines, Enums::DisplayLevel displayLevel = Enums::DisplayLevel::Player);
    static void Clear();
    static void SetDisplayLevel(Enums::DisplayLevel displayLevel);
    static void SetWindowSize(int width, int height);

    template<typename T>
    static T GetInput(std::string_view message);

    static void WaitForAnyKey(const std::string& message);
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