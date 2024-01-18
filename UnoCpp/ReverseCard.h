#pragma once
#include "BaseCard.h"
class ReverseCard : public BaseCard
{
public:
	ReverseCard(std::shared_ptr<TurnHandler> turnHandler, std::shared_ptr<BaseCard> myPointer, Enums::CardColor color, std::string symbol);
};

