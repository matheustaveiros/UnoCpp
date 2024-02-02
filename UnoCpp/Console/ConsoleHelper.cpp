#include <conio.h>
#include <windows.h>
#include "ConsoleHelper.h"

constexpr auto BACKGROUNDED_RED = 0x0004;
constexpr auto BACKGROUNDED_BLUE = 0x0001;
constexpr auto BACKGROUNDED_GREEN = 0x0002;
constexpr auto BACKGROUNDED_YELLOW = 0x0006;

Enums::DisplayLevel ConsoleHelper::_displayLevel;

void ConsoleHelper::PrintMessage(std::string_view message, Enums::CardColor textColor, Enums::DisplayLevel displayLevel)
{
    if (displayLevel == Enums::DisplayLevel::Developer && _displayLevel == Enums::DisplayLevel::Player)
        return;

    SetTextColorByCardColor(textColor);
    std::cout << message;
    ResetTextColor();
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

void ConsoleHelper::WaitForAnyKey(const std::string& message, Enums::CardColor textColor)
{
    SetTextColorByCardColor(textColor);
    PrintMessage(message, textColor, Enums::DisplayLevel::Player);
    ResetTextColor();
    _getch();
}

void ConsoleHelper::SetTextColorByCardColor(Enums::CardColor color)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    using enum Enums::CardColor;
    switch (color)
    {
    case Red:
        SetConsoleTextAttribute(console, BACKGROUNDED_RED | FOREGROUND_INTENSITY);
        break;
    case Blue:
        SetConsoleTextAttribute(console, BACKGROUNDED_BLUE | FOREGROUND_INTENSITY);
        break;
    case Green:
        SetConsoleTextAttribute(console, BACKGROUNDED_GREEN | FOREGROUND_INTENSITY);
        break;
    case Yellow:
        SetConsoleTextAttribute(console, BACKGROUNDED_YELLOW | FOREGROUND_INTENSITY);
        break;
    default:
        break;
    }
}

void ConsoleHelper::ResetTextColor()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
