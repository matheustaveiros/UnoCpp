#pragma once
#include "BaseAction.h"
class JumpPlayerAction : public BaseAction
{
public:
	explicit JumpPlayerAction(std::shared_ptr<TurnHandler> turnHandler);
	void Execute() override;
};

