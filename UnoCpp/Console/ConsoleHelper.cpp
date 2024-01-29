#include <conio.h>
#include <windows.h>
#include "ConsoleHelper.h"

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

void ConsoleHelper::SetWindowSize(int width, int height)
{
    // Set console window size
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the console window size and buffer size
    COORD size{};
    size.X = static_cast<SHORT>(width / 5);  // You can adjust this as needed
    size.Y = static_cast<SHORT>(height / 5);  // You can adjust this as needed
    SetConsoleScreenBufferSize(console, size);

    SMALL_RECT windowSize{};
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = size.X - 1;
    windowSize.Bottom = size.Y - 1;
    SetConsoleWindowInfo(console, TRUE, &windowSize);
}

void ConsoleHelper::WaitForAnyKey(const std::string& message)
{
    PrintMessage(message, Enums::DisplayLevel::Player);
    _getch();
}