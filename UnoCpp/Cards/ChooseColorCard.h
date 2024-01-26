#pragma once
#include "BaseCard.h"
class ChooseColorCard : public BaseCard
{
public:
	ChooseColorCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol);
};

