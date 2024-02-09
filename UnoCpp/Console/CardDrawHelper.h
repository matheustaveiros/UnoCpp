#pragma once
#include <memory>
#include <windows.h>
#include <windef.h>
#include <vector>
class BaseCard;
class CardDrawHelper
{
private:
	static COORD GetCurrentCursorPosition();
	static bool WillExceedConsoleWidth(const COORD& currentPosition, int spaceOffset);

public:
	static void DrawCards(std::span<BaseCard*> cards);
	static void DrawCard(BaseCard* card, int id = -1);
	static void SetTextColorByCardColor(BaseCard* card, const HANDLE console);
	static void DrawCard(BaseCard* card, COORD position, int id = -1);
};

