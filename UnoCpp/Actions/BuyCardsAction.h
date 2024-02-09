#pragma once
#include "BaseAction.h"
class BuyCardsAction : public BaseAction
{
private:
	int _amount;

public:
	BuyCardsAction(TurnHandler* turnHandler, int amount);

	void Execute() override;
};

