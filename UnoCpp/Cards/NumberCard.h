#pragma once
#include "BaseCard.h"
class NumberCard : public BaseCard
{
public:
	NumberCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol);
};

