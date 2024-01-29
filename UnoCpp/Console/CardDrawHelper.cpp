#include <iostream>
#include <vector>
#include <string>
#include "Cards/BaseCard.h"
#include "Utils/Enums.h"
#include "CardDrawHelper.h"

#define NOMINMAX

constexpr auto BACKGROUNDED_RED = 0x00047;
constexpr auto BACKGROUNDED_BLUE = 0x00017;
constexpr auto BACKGROUNDED_GREEN = 0x00027;
constexpr auto BACKGROUNDED_YELLOW = 0x00067;
constexpr auto BACKGROUNDED_BLACK = 0x0087;

COORD CardDrawHelper::GetCurrentCursorPosition()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(console, &screenBufferInfo);
    return screenBufferInfo.dwCursorPosition;
}

bool CardDrawHelper::WillExceedConsoleWidth(const COORD& currentPosition, int spaceOffset)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(console, &screenBufferInfo);

    return (currentPosition.X + spaceOffset) >= screenBufferInfo.dwSize.X;
}

void CardDrawHelper::DrawCards(const std::vector<std::shared_ptr<BaseCard>>& cards)
{
    COORD currentPosition = GetCurrentCursorPosition();
    for (int i = 0; i < cards.size(); i++)
    {
        int spaceOffset = std::max<int>(11, static_cast<int>(cards[i]->GetSymbol().length()) + 2);

        if (WillExceedConsoleWidth(currentPosition, spaceOffset))
        {
            currentPosition.X = 0;
            currentPosition.Y += 6;
        }

        DrawCard(cards[i], currentPosition, i);
        currentPosition.X += spaceOffset;
    }
}

void CardDrawHelper::DrawCard(std::shared_ptr<BaseCard> card, int id)
{
    COORD currentPosition = GetCurrentCursorPosition();
    DrawCard(card, currentPosition, id);
}

void CardDrawHelper::SetTextColorByCardColor(std::shared_ptr<BaseCard> card, const HANDLE console)
{
    using enum Enums::CardColor;
    switch (card->GetColor())
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
    case Black:
        SetConsoleTextAttribute(console, BACKGROUNDED_BLACK | FOREGROUND_INTENSITY);
        break;
    default:
        break;
    }
}

void CardDrawHelper::DrawCard(std::shared_ptr<BaseCard> card, COORD position, int id)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);

    SetTextColorByCardColor(card, console);

    int cardWidth = static_cast<int>(card->GetSymbol().length()) + 4;

    //Top
    std::cout << "+";
    for (int i = 0; i < cardWidth; ++i)
    {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    //Mid-Top Blank
    const SHORT yOffsetOne = position.Y + 1;
    SetConsoleCursorPosition(console, { position.X, yOffsetOne });
    std::cout << "|";
    for (int i = 0; i < cardWidth; ++i)
    {
        std::cout << " ";
    }
    std::cout << "|" << std::endl;

    //Mid Symbol
    const SHORT yOffsetTwo = position.Y + 2;
    SetConsoleCursorPosition(console, { position.X, yOffsetTwo });
    std::cout << "|  " << card->GetSymbol() << "  |" << std::endl;

    //Mid Blank
    const SHORT yOffsetThree = position.Y + 3;
    SetConsoleCursorPosition(console, { position.X, yOffsetThree });
    std::cout << "|";
    for (int i = 0; i < cardWidth; ++i)
    {
        std::cout << " ";
    }
    std::cout << "|" << std::endl;

    //Bottom
    const SHORT yOffsetFour = position.Y + 4;
    SetConsoleCursorPosition(console, { position.X, yOffsetFour });
    std::cout << "+";
    for (int i = 0; i < cardWidth; ++i)
    {
        std::cout << "-";
    }
    std::cout << "+" << std::endl;

    // Reset text color to default
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    //Show Id
    if (id != -1)
    {
        SHORT xOffset = position.X + (static_cast<SHORT>(cardWidth) / 2) + 1;
        const SHORT yOffset = position.Y + 5;
        SetConsoleCursorPosition(console, { xOffset , yOffset });
        std::cout << std::to_string(id) << std::endl;
    }
}
