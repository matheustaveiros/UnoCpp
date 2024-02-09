#include "BaseCard.h"
#include "Core/TurnHandler.h"

BaseCard::BaseCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol)
	: _turnHandler{ turnHandler }, _color{ color }, _symbol{ symbol }
{
	
}

Enums::CardColor BaseCard::GetColor() const
{
	return _color;
}

std::string_view BaseCard::GetSymbol() const
{
	return _symbol;
}

void BaseCard::AddAction(BaseAction* baseAction)
{
	_baseActions.emplace_back(baseAction);
}

void BaseCard::Execute()
{
	_turnHandler->UseCard(this);
}

std::span<BaseAction*> BaseCard::GetActions()
{
	return std::span(_baseActions);
}
