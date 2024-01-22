#pragma once
#include "BaseCard.h"
class ReverseCard : public BaseCard
{
public:
	ReverseCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, std::string symbol);
};

