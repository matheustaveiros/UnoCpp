#pragma once
#include "BaseCard.h"
class JumpCard : public BaseCard
{
public:
	JumpCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol);
};

