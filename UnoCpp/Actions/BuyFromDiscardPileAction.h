#pragma once
#include "BaseAction.h"
class BuyFromDiscardPileAction : public BaseAction
{
private:
	int _amount;

public:
	BuyFromDiscardPileAction(TurnHandler* turnHandler, int amount);

	void Execute() override;
};

