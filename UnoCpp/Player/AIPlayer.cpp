#include "AIPlayer.h"
#include <unordered_map>

void AIPlayer::CalculateThrowCardInput()
{
	SetUnoStateIfRequired();

	int selectedOption = GetBestCardOption();

	if (selectedOption != -1)
	{
		UseOption(selectedOption);
	}
	else
	{
		HandleBuyCardOption();
		CalculateThrowCardInput();
	}
}

void AIPlayer::CalculateSelectColorInput()
{
	_turnHandler->SetSelectedColor(static_cast<int>(GetColorByAmountInHand()));
}

void AIPlayer::SetUnoStateIfRequired()
{
	if (GetCards().size() == 2)
	{
		SetUnoState(true);
	}
}

int AIPlayer::GetBestCardOption()
{
	int bestOption = -1;
	int currentBestWeight = -1;

	for (int i = 0; i < GetCards().size(); i++)
	{
		const std::shared_ptr<BaseCard>& card = GetCard(i);
		if (CardIsCompatible(card))
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