#pragma once
#include "BaseCard.h"
class NumberCard : public BaseCard
{
public:
	NumberCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol);
};

