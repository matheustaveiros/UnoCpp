#pragma once
#include "BaseCard.h"
class PlusTwoCard : public BaseCard
{
private:
	const int CARDS_TO_BUY = 2;

public:
	PlusTwoCard(std::shared_ptr<BaseCard> myPointer);
};

