#include <memory>
#include "Actions/GoToNextPlayerAction.h"
#include "Actions/AskForAColorAction.h"
#include "ChooseColorCard.h"

ChooseColorCard::ChooseColorCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string& symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto askForAColorAction = std::make_shared<AskForAColorAction>(_turnHandler);
	AddAction(askForAColorAction);

	auto goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction);
}