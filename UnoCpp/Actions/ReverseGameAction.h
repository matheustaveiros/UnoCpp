#pragma once
#include "BaseAction.h"
class ReverseGameAction : public BaseAction
{
public:
	explicit ReverseGameAction(std::shared_ptr<TurnHandler> turnHandler);

	void Execute() override;
};

