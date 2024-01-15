#pragma once
#include "BaseAction.h"
class BuyCardsAction : public BaseAction
{
private:
	int _amount;

public:
	BuyCardsAction(std::shared_ptr<TurnHandler> turnHandler, int amount);

	void Execute() override;
};

