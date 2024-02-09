#pragma once
#include "BaseCard.h"
class JumpCard : public BaseCard
{
public:
	JumpCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol);
};

