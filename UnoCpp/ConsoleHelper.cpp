#include "ConsoleHelper.h"
#include <conio.h>

Enums::DisplayLevel ConsoleHelper::_displayLevel;

void ConsoleHelper::PrintMessage(std::string_view message, Enums::DisplayLevel displayLevel)
{
    if (displayLevel == Enums::DisplayLevel::Developer && _displayLevel == Enums::DisplayLevel::Player)
        return;

    std::cout << message;
}

void ConsoleHelper::PrintMessage(const std::vector<std::string_view>& lines, Enums::DisplayLevel displayLevel)
{
    std::string fullMessage { };
    for (const std::string_view msg : lines)
    {
        fullMessage += msg;
        fullMessage += "\n";
    }

    PrintMessage(fullMessage, displayLevel);
}

void ConsoleHelper::Clear()
{
    system("cls");
}

void ConsoleHelper::SetDisplayLevel(Enums::DisplayLevel displayLevel)
{
    _displayLevel = displayLevel;
}

void ConsoleHelper::WaitForAnyKey(const std::string& message)
{
    PrintMessage(message, Enums::DisplayLevel::Player);
    _getch();
}