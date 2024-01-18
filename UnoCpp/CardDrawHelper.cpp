#include "CardDrawHelper.h"
#include <iostream>
#include <vector>
#include <string>
#include "BaseCard.h"
#include "Enums.h"
#define NOMINMAX
#define FOREGROUND_YELLOW     0x0006

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

void CardDrawHelper::DrawCards(std::vector<std::shared_ptr<BaseCard>> cards)
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

void CardDrawHelper::DrawCard(std::shared_ptr<BaseCard> card, COORD position, int id)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);

    if (card->GetColor() == Enums::CardColor::Red)
    {
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
    else if (card->GetColor() == Enums::CardColor::Blue)
    {
        SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    }
    else if (card->GetColor() == Enums::CardColor::Green)
    {
        SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }
    else if (card->GetColor() == Enums::CardColor::Yellow)
    {
        SetConsoleTextAttribute(console, FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
    }

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
        SHORT xOffset = position.X + (cardWidth / 2.0) + 1.0;
        const SHORT yOffset = position.Y + 5;
        SetConsoleCursorPosition(console, { xOffset , yOffset });
        std::cout << std::to_string(id) << std::endl;
    }
}
