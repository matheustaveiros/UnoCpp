#include "BaseCard.h"

Enums::CardColor BaseCard::GetColor() const
{
	return _color;
}

std::string BaseCard::GetSymbol() const
{
	return _symbol;
}

void BaseCard::AddAction(BaseAction& baseAction)
{
	_baseActions.push_back(baseAction);
}

void BaseCard::Execute()
{
	_turnHandler->UseCard(*this);
}

std::vector<BaseAction>& BaseCard::GetActions()
{
	return _baseActions;
}

