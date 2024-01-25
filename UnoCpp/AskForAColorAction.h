#pragma once
#include "BaseAction.h"
class AskForAColorAction : public BaseAction
{
public:
	explicit AskForAColorAction(std::shared_ptr<TurnHandler> turnHandler);
	void Execute() override;
};