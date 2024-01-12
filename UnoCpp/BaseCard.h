#pragma once

#include "Enums.h"
#include <string>
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

protected:
	std::shared_ptr<TurnHandler> _turnHandler;

public:
	Enums::CardColor GetColor() const;
	std::string GetSymbol() const;

	virtual void Awake() = 0;
	void AddAction(BaseAction& baseAction);
	void Execute();
	std::vector<BaseAction> GetActions();

	virtual ~BaseCard() = default;
};

