#include "Player.h"

void Player::StartTurn()
{
}

Player::Player(std::shared_ptr<TurnHandler> turnHandler, std::string name) : _turnHandler{ turnHandler }, _name { name }
{
	
}

void Player::DrawCards()
{

}

void Player::ShowActions()
{
}

bool Player::HasValidActions(std::shared_ptr<BaseCard> cardToCompare)
{
	if (&cardToCompare != nullptr)
	{
		//Search in Hand for Equal Card
	}
	else {
		//Get top card on deck
		//Compare the Color if matches
		//else if Compare the symbol
	}

	return false;
}

void Player::ValidateCardCount()
{
	if (_cardsInHand.empty())
	{
		DispatchWinCondition();
	}
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
	if (option == YELL_UNO_OPTION_INDEX)
	{
		//Display Yell Uno
		_inUnoState = true;
	}
	else {
		std::shared_ptr<BaseCard> currentUseCard = _cardsInHand[option];
		_turnHandler->UseCard(currentUseCard);
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