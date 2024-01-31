#include "BaseCard.h"
#include "Core/TurnHandler.h"

BaseCard::BaseCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol)
	: _turnHandler{ turnHandler }, _color{ color }, _symbol{ symbol }
{
	
}

Enums::CardColor BaseCard::GetColor() const
{
	return _color;
}

std::string BaseCard::GetSymbol() const
{
	return _symbol;
}

void BaseCard::AddAction(std::shared_ptr<BaseAction> baseAction)
{
	_baseActions.emplace_back(baseAction);
}

void BaseCard::Execute()
{
	_turnHandler->UseCard(GetPointer());
}

const std::vector<std::shared_ptr<BaseAction>>& BaseCard::GetActions() const
{
	return _baseActions;
}
