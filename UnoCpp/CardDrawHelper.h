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
	static void DrawCards(std::vector<std::shared_ptr<BaseCard>> cards);
	static void DrawCard(std::shared_ptr<BaseCard> card, int id = -1);
	static void DrawCard(std::shared_ptr<BaseCard> card, COORD position, int id = -1);
};

