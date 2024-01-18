#pragma once
#include "BaseCard.h"
class NumberCard : public BaseCard
{
public:
	NumberCard(std::shared_ptr<TurnHandler> turnHandler, std::shared_ptr<BaseCard> myPointer, Enums::CardColor color, std::string symbol);
};

