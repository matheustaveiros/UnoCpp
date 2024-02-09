#pragma once
#include "BaseAction.h"
class JumpPlayerAction : public BaseAction
{
public:
	explicit JumpPlayerAction(TurnHandler* turnHandler);
	void Execute() override;
};

