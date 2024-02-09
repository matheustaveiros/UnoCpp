#pragma once
#include "BaseAction.h"
class ReverseGameAction : public BaseAction
{
public:
	explicit ReverseGameAction(TurnHandler* turnHandler);

	void Execute() override;
};

