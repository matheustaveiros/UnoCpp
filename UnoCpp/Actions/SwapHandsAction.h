#pragma once
#include "BaseAction.h"
class SwapHandsAction : public BaseAction
{

public:
	explicit SwapHandsAction(std::shared_ptr<TurnHandler> turnHandler);
	void Execute() override;
};