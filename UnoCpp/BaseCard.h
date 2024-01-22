#pragma once

#include "Enums.h"
#include <string>
#include "BaseAction.h"
#include <vector>
#include <memory>

class BaseAction;
class TurnHandler;
class BaseCard : private std::enable_shared_from_this<BaseCard>
{

private:
	Enums::CardColor _color;
	std::string _symbol;
	std::vector<std::shared_ptr<BaseAction>> _baseActions;

	std::shared_ptr<BaseCard> GetPointer()
	{
		return shared_from_this();
	}

public:
	BaseCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, std::string symbol);

	std::shared_ptr<TurnHandler> _turnHandler;

	Enums::CardColor GetColor() const;
	std::string GetSymbol() const;

	void AddAction(std::shared_ptr<BaseAction> baseAction);
	void Execute();
	std::vector<std::shared_ptr<BaseAction>> GetActions();

	virtual ~BaseCard() = default;
};

