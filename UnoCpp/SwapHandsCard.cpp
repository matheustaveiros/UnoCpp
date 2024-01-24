#include "SwapHandsCard.h"
#include "GoToNextPlayerAction.h"
#include "SwapHandsAction.h"
SwapHandsCard::SwapHandsCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto swapHandsAction = std::make_shared<SwapHandsAction>(_turnHandler);
	AddAction(swapHandsAction);

	auto goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction);
}