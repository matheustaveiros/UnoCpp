#include "Actions/GoToNextPlayerAction.h"
#include "Actions/SwapHandsAction.h"
#include "SwapHandsCard.h"
SwapHandsCard::SwapHandsCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto swapHandsAction = std::make_unique<SwapHandsAction>(_turnHandler);
	AddAction(swapHandsAction.get());

	auto goToNextPlayerAction = std::make_unique<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction.get());
}