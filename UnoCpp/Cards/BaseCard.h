#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Utils/Enums.h"
#include "Actions/BaseAction.h"

class BaseAction;
class TurnHandler;
class BaseCard
{
protected:
	TurnHandler* _turnHandler;

private:
	Enums::CardColor _color;
	std::string _symbol;
	std::vector<BaseAction*> _baseActions;

public:
	BaseCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol);

	Enums::CardColor GetColor() const;
	std::string_view GetSymbol() const;

	void AddAction(BaseAction* baseAction);
	void Execute();
	std::span<BaseAction*> GetActions();

	virtual ~BaseCard() = default;
};

