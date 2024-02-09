#include "Player.h"

Player::Player(TurnHandler* turnHandler, const std::string_view name) : _turnHandler{ turnHandler }, _name{ name }
{

}

void Player::DrawTopCardFromDiscardPile()
{
    if (_turnHandler->GetMandatoryColor() != Enums::CardColor::Empty && !_turnHandler->HasCardsStacked())
    {
        ConsoleHelper::PrintMessage(std::format("A Mandatory Color is required For This Turn, Color: {}\n",
            Enums::GetColorDisplayName(_turnHandler->GetMandatoryColor())), _turnHandler->GetMandatoryColor());
    }

    ConsoleHelper::PrintMessage("Current Top Card is:\n");
    CardDrawHelper::DrawCard(_turnHandler->GetTopCardFromDiscardPile());
}

void Player::DrawCards()
{
    ConsoleHelper::PrintMessage(std::format("Player {} Hand:\n", GetName()));
    CardDrawHelper::DrawCards(GetCards());
}

bool Player::HasValidCardWithSymbolInHand()
{
    for (BaseCard* card : _cardsInHand)
    {
        if (CardIsSymbolOnlyCompatible(card))
            return true;
    }

	return false;
}

bool Player::CanWin() const
{
	return static_cast<int>(_cardsInHand.size()) - 1 == 0;
}

bool Player::CardIsCompatible(const BaseCard* card) const
{
    if (card->GetColor() == Enums::CardColor::Black)
        return true;
    if (_turnHandler->GetMandatoryColor() != Enums::CardColor::Empty)
    {
        if (card->GetColor() == _turnHandler->GetMandatoryColor())
        {
            _turnHandler->ResetMandatoryColor();
            return true;
        }
        else
        {
            return false;
        }
    }

	const BaseCard* cardFromDiscardPile = _turnHandler->GetTopCardFromDiscardPile();
	if (card->GetSymbol() == cardFromDiscardPile->GetSymbol())
		return true;
	if (card->GetColor() == cardFromDiscardPile->GetColor())
		return true;

	return false;
}

bool Player::CardIsSymbolOnlyCompatible(const BaseCard* card)
{
    const BaseCard* cardFromDiscardPile = _turnHandler->GetTopCardFromDiscardPile();
    return card->GetSymbol() == cardFromDiscardPile->GetSymbol();
}

void Player::DispatchWinCondition()
{
	ConsoleHelper::PrintMessage("Victory! Player: " + _name + " Won the Game\n", Enums::CardColor::Green);
	_turnHandler->SetGameState(false);
}

void Player::AddCardToHand(BaseCard* card)
{
	_cardsInHand.emplace_back(card);
}

void Player::HandleYellUnoOption()
{
    if (_cardsInHand.size() <= 2)
    {
        _inUnoState = true;
        ConsoleHelper::PrintMessage("Player: " + _name + " Yelled Uno!\n", Enums::CardColor::Yellow);
        StartTurn();
    }
    else
    {
        ConsoleHelper::PrintMessage("Can't Yell Uno Yet, Consider Yelling When You Have 2 Cards In Hand\n", Enums::CardColor::Red);
        StartTurn();
    }
}

void Player::HandleBuyCardOption()
{
    _turnHandler->BuyCardsFromDeck(1);
}

void Player::HandleUseCardOption(int option)
{
    BaseCard* currentUseCard;

    if (option < _cardsInHand.size())
        currentUseCard = _cardsInHand[option];

    if (currentUseCard != nullptr && CardIsCompatible(currentUseCard))
    {
        if (CanWin())
        {
            HandleWinCondition(currentUseCard, option);
        }
        else
        {
            HandleCardUsage(currentUseCard, option);
        }
    }
    else
    {
        if (_turnHandler->GetMandatoryColor() != Enums::CardColor::Empty)
        {
            ConsoleHelper::PrintMessage(std::format("A Mandatory Color is required For This Turn, Color: {}\n",
                Enums::GetColorDisplayName(_turnHandler->GetMandatoryColor())), _turnHandler->GetMandatoryColor());
        }
        else
        {
            ConsoleHelper::PrintMessage("Invalid Action, Please Select a Card With Compatible Symbol or Color\n", Enums::CardColor::Red);
        }

        StartTurn();
    }
}

void Player::HandleWinCondition(const BaseCard* currentUseCard, int option)
{
    if (_inUnoState)
    {
        DispatchWinCondition();
    }
    else
    {
        ConsoleHelper::PrintMessage("Player Will Suffer Yell UNO! Penalty:\n", Enums::CardColor::Red);
        _turnHandler->BuyCardsFromDeck(DeckData::PENALTY_FOR_NOT_YELL_UNO);
        _cardsInHand.erase(_cardsInHand.begin() + option);
        _turnHandler->UseCard(currentUseCard);
        TurnEnded();
    }
}

void Player::HandleCardUsage(const BaseCard* currentUseCard, int option)
{
    _cardsInHand.erase(_cardsInHand.begin() + option);
    _turnHandler->UseCard(currentUseCard);
    TurnEnded();
}

void Player::TurnEnded()
{
	if (_inUnoState && static_cast<int>(_cardsInHand.size()) > 1)
	{
		_inUnoState = false;
	}
}

void Player::SetUnoState(bool unoState)
{
    _inUnoState = unoState;
}

std::span<BaseCard*> Player::GetCards()
{
	return std::span(_cardsInHand);
}

BaseCard* Player::GetCard(int index) const
{
    return _cardsInHand[index];
}

void Player::CleanPlayerHand()
{
	_cardsInHand.clear();
}

void Player::ReplaceCardsInHand(const std::span<BaseCard*> cards)
{
    _cardsInHand = cards;
}

std::string_view Player::GetName() const
{
	return _name;
}