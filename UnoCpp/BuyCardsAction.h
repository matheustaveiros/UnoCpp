#pragma once
#include "BaseAction.h"
class BuyCardsAction : public BaseAction
{
private:
	int _amount;

public:
	BuyCardsAction(int amount);

	void Execute() override { };
};

