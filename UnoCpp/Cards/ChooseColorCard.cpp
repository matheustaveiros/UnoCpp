#include <memory>
#include "Actions/GoToNextPlayerAction.h"
#include "Actions/AskForAColorAction.h"
#include "ChooseColorCard.h"

ChooseColorCard::ChooseColorCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto askForAColorAction = std::make_unique<AskForAColorAction>(_turnHandler);
	AddAction(askForAColorAction.get());

	auto goToNextPlayerAction = std::make_unique<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction.get());
}