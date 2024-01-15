#include "BaseCard.h"
#include "TurnHandler.h"

BaseCard::BaseCard(std::shared_ptr<BaseCard> myPointer) : _myPointer { myPointer }
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
	_turnHandler->UseCard(_myPointer);
}

std::vector<std::shared_ptr<BaseAction>> BaseCard::GetActions()
{
	return _baseActions;
}
