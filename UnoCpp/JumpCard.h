#pragma once
#include "BaseCard.h"
class JumpCard : public BaseCard
{
public:
	JumpCard(std::shared_ptr<BaseCard> myPointer, Enums::CardColor color, std::string symbol);
};

