#pragma once

#include "Enums.h"
#include <string>
#include "BaseAction.h"
#include <vector>
#include <memory>

class BaseAction;
class TurnHandler;
class BaseCard
{
private:
	Enums::CardColor _color;
	std::string _symbol;
	std::vector<BaseAction> _baseActions;

public:
	std::shared_ptr<TurnHandler> _turnHandler;

	Enums::CardColor GetColor() const;
	std::string GetSymbol() const;

	virtual void Awake() = 0;
	void AddAction(BaseAction& baseAction);
	void Execute();
	std::vector<BaseAction> GetActions();

	virtual ~BaseCard() = default;
};

