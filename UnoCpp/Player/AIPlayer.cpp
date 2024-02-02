#include "AIPlayer.h"
#include <unordered_map>

AIPlayer::AIPlayer(std::shared_ptr<TurnHandler> turnHandler, const std::string& name) : Player(turnHandler, name)
{

}

void AIPlayer::StartTurn()
{
	SetUnoStateIfRequired();

	DrawCards();

	if (_turnHandler->HasCardsStacked())
	{
		CalculateThrowCardInput(true);
	}
	else
	{
		CalculateThrowCardInput(false);
	}
}

void AIPlayer::AskToSelectAColor()
{
	DrawTopCardFromDiscardPile();
	CalculateSelectColorInput();
	ConsoleHelper::WaitForAnyKey("Press Any Key to Continue\n", Enums::CardColor::Yellow);
	ConsoleHelper::Clear();
}

void AIPlayer::CalculateThrowCardInput(bool checkSymbolOnly)
{
	int selectedOption = GetBestCardOption(checkSymbolOnly);

	if (selectedOption != -1)
	{
		HandleUseCardOption(selectedOption);
		ConsoleHelper::WaitForAnyKey("Press Any Key to Continue\n", Enums::CardColor::Yellow);
		ConsoleHelper::Clear();
	}
	else if(checkSymbolOnly)
	{
		ConsoleHelper::PrintMessage("No Compatible Cards to Throw\n", Enums::CardColor::Red);
		_turnHandler->ApplyStackCardsToPlayer();
		_turnHandler->SkipToNextPlayer();
	}
	else
	{
		HandleBuyCardOption();
		DrawCards();
		ConsoleHelper::WaitForAnyKey("Press Any Key to Continue\n", Enums::CardColor::Yellow);
		ConsoleHelper::Clear();
		CalculateThrowCardInput(checkSymbolOnly);
	}
}

void AIPlayer::SetUnoStateIfRequired()
{
	if (GetCards().size() <= 2)
	{
		SetUnoState(true);
		ConsoleHelper::PrintMessage(std::format("Player: {} Yelled Uno!\n", GetName()), Enums::CardColor::Yellow);
	}
}

void AIPlayer::CalculateSelectColorInput()
{
	_turnHandler->SetSelectedColor(static_cast<int>(GetColorByAmountInHand()));
}

int AIPlayer::GetBestCardOption(bool checkSymbolOnly)
{
	int bestOption = -1;
	int currentBestWeight = -1;

	for (int i = 0; i < GetCards().size(); i++)
	{
		const std::shared_ptr<BaseCard>& card = GetCard(i);

		bool isCompatible = checkSymbolOnly ? CardIsSymbolOnlyCompatible(card) : CardIsCompatible(card);

		if (isCompatible)
		{
			int sameSymbolAmount = GetAmountBySymbol(card->GetSymbol());
			int sameColorAmount = GetAmountByColor(card->GetColor());
			int weight = sameSymbolAmount + sameColorAmount;

			if (weight > currentBestWeight)
			{
				bestOption = i;
				currentBestWeight = weight;
			}
		}
	}

	return bestOption;
}

int AIPlayer::GetAmountBySymbol(std::string_view symbol) const
{
	int amount = 0;
	for (const std::shared_ptr<BaseCard>& card : GetCards())
	{
		if (card->GetSymbol() == symbol)
			amount++;
	}

	return amount;
}

int AIPlayer::GetAmountByColor(const Enums::CardColor& color) const
{
	int amount = 0;
	for (const std::shared_ptr<BaseCard>& card : GetCards())
	{
		if (card->GetColor() == color)
			amount++;
	}

	return amount;
}

Enums::CardColor AIPlayer::GetColorByAmountInHand() const
{
	std::unordered_map<Enums::CardColor, int> amountByColor;
	for (const std::shared_ptr<BaseCard>& card : GetCards())
	{
		if (card->GetColor() == Enums::CardColor::Black)
			continue;

		if (amountByColor.contains(card->GetColor()))
		{
			amountByColor[card->GetColor()] += 1;
		}
		else
		{
			amountByColor.insert(std::make_pair(card->GetColor(), 1));
		}
	}

	int bestWeight = 0;
	Enums::CardColor selectedColor = Enums::CardColor::Blue;
	for (const auto& [color, weight] : amountByColor)
	{
		if (weight > bestWeight)
		{
			selectedColor = color;
			bestWeight = weight;
		}
	}
	
	return selectedColor;
}