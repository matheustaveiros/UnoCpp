#pragma once
#include "BaseCard.h"
class SwapHandsCard : public BaseCard
{
public:
	SwapHandsCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string& symbol);
};

