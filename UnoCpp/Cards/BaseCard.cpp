#include "BaseCard.h"
#include "../Core/TurnHandler.h"

BaseCard::BaseCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol)
	: _color{ color }, _symbol{ symbol }, _turnHandler{ turnHandler }
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
	_baseActions.push_back(baseAction);
}

void BaseCard::Execute()
{
	_turnHandler->UseCard(GetPointer());
}

std::vector<std::shared_ptr<BaseAction>> BaseCard::GetActions() const
{
	return _baseActions;
}
