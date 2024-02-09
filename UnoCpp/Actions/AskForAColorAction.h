#pragma once
#include "BaseAction.h"
class AskForAColorAction : public BaseAction
{
public:
	explicit AskForAColorAction(TurnHandler* turnHandler);
	void Execute() override;
};