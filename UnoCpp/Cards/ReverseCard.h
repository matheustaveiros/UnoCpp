#pragma once
#include "BaseCard.h"
class ReverseCard : public BaseCard
{
public:
	ReverseCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string& symbol);
};

