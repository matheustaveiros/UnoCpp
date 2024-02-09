#pragma once
#include "BaseCard.h"
class ChooseColorCard : public BaseCard
{
public:
	ChooseColorCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string& symbol);
};

