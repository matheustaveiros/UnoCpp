#pragma once
#include "BaseAction.h"
class SwapHandsAction : public BaseAction
{

public:
	explicit SwapHandsAction(TurnHandler* turnHandler);
	void Execute() override;
};