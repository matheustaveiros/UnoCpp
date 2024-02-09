#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Utils/Enums.h"

class ConsoleHelper
{
private:
    static Enums::DisplayLevel _displayLevel;
    static void SetTextColorByCardColor(Enums::CardColor color);
    static void ResetTextColor();

public:
    
    static void PrintMessage(const std::string&, Enums::CardColor textColor = Enums::CardColor::Empty, Enums::DisplayLevel displayLevel = Enums::DisplayLevel::Player);
    static void Clear();
    static void SetDisplayLevel(Enums::DisplayLevel displayLevel);
    static void SetWindowSize(int width, int height);

    template<typename T>
    static T GetInput(std::string_view message, Enums::CardColor textColor = Enums::CardColor::Empty);

    static void WaitForAnyKey(const std::string_view message, Enums::CardColor textColor = Enums::CardColor::Empty);
};

template <typename T>
T ConsoleHelper::GetInput(std::string_view message, Enums::CardColor textColor)
{
    T input{};

    SetTextColorByCardColor(textColor);
    std::cout << message;
    ResetTextColor();

    std::cin >> std::ws >> input;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        return GetInput<T>(message);
    }

    return input;
}