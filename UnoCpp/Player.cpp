#include "Player.h"
#include "ConsoleHelper.h"
#include "CardDrawHelper.h"
#include "DeckData.h"

void Player::StartTurn()
{
	DrawCards();
	ShowExtraActions();
	WaitForActionInput();
}

Player::Player(std::shared_ptr<TurnHandler> turnHandler, std::string name) : _turnHandler{ turnHandler }, _name{ name }
{

}

void Player::DrawCards()
{
	ConsoleHelper::PrintMessage("Player Hand:\n");
	CardDrawHelper::DrawCards(_cardsInHand);
}

void Player::ShowExtraActions()
{
	int startOffset = static_cast<int>(_cardsInHand.size());
	_buyCardActionValue = startOffset;
	_yellUnoActionValue = startOffset + 1;

	ConsoleHelper::PrintMessage("Type Any Card Id to Use Or\n");
	ConsoleHelper::PrintMessage("Type " + std::to_string(_buyCardActionValue) + " to Buy One Card\n");
	ConsoleHelper::PrintMessage("Type " + std::to_string(_yellUnoActionValue) + " to Yell Uno\n");
}

void Player::WaitForActionInput()
{
	int selectedAction = ConsoleHelper::GetInput<int>("Insert the number of the action to Play: \n");
	UseOption(selectedAction);
}

bool Player::HasValidActions(std::shared_ptr<BaseCard> cardToCompare)
{
	if (&cardToCompare != nullptr) // in case of a special card
	{
		for (int i = 0; i < _cardsInHand.size(); i++)
		{
			if (_cardsInHand[i]->GetSymbol() == cardToCompare->GetSymbol())
				return true;
		}
	}
	else {
		for (int i = 0; i < _cardsInHand.size(); i++)
		{
			bool isCompatible = CardIsCompatible(_cardsInHand[i]);

			if (isCompatible)
				return true;
		}
	}

	return false;
}

bool Player::CanWin()
{
	return static_cast<int>(_cardsInHand.size()) - 1 == 0;
}

bool Player::CardIsCompatible(std::shared_ptr<BaseCard> card)
{
	std::shared_ptr<BaseCard> cardFromDiscardPile = _turnHandler->GetTopCardFromDiscardPile();
	if (card->GetSymbol() == cardFromDiscardPile->GetSymbol())
		return true;
	if (card->GetColor() == cardFromDiscardPile->GetColor())
		return true;

	return false;
}

void Player::DispatchWinCondition()
{
}

void Player::AddCardToHand(std::shared_ptr<BaseCard> card)
{
	_cardsInHand.push_back(card);
}

void Player::UseOption(int option)
{
	ConsoleHelper::Clear();
	if (option == _yellUnoActionValue)
	{
		_inUnoState = true;

		ConsoleHelper::PrintMessage("Player: " + _name + " Yelled Uno!\n");

		StartTurn();
	}
	else if (option == _buyCardActionValue)
	{
		_turnHandler->BuyCardsFromDeck(1);
	}
	else
	{
		std::shared_ptr<BaseCard> currentUseCard = _cardsInHand[option];
		if (CardIsCompatible(currentUseCard))
		{
			if (CanWin())
			{
				if (_inUnoState)
				{
					DispatchWinCondition();
				}
				else
				{
					ConsoleHelper::PrintMessage("Player Will Suffer Yell UNO! Penalty:\n");

					_turnHandler->BuyCardsFromDeck(DeckData::PENALTY_FOR_NOT_YELL_UNO);
					_cardsInHand.erase(_cardsInHand.begin() + option);
					_turnHandler->UseCard(currentUseCard);
				}
			}
			else
			{
				_cardsInHand.erase(_cardsInHand.begin() + option);
				_turnHandler->UseCard(currentUseCard);
			}
		}
		else
		{
			ConsoleHelper::PrintMessage("Invalid Action, Please Select a Card With Compatible Symbol or Color\n");
			WaitForActionInput();
		}
	}
}

std::vector<std::shared_ptr<BaseCard>> Player::GetCards()
{
	return _cardsInHand;
}

void Player::CleanPlayerHand()
{
	_cardsInHand.clear();
}

std::string& Player::GetName()
{
	return _name;
}