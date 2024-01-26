#pragma once
#include "BaseCard.h"
class SwapHandsCard : public BaseCard
{
public:
	SwapHandsCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol);
};

