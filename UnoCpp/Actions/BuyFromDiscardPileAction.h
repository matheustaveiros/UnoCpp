#pragma once
#include "BaseAction.h"
class BuyFromDiscardPileAction : public BaseAction
{
private:
	int _amount;

public:
	BuyFromDiscardPileAction(std::shared_ptr<TurnHandler> turnHandler, int amount);

	void Execute() override;
};

