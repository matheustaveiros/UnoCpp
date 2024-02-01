#include "Player.h"

Player::Player(std::shared_ptr<TurnHandler> turnHandler, const std::string& name) : _turnHandler{ turnHandler }, _name{ name }
{

}

void Player::DrawTopCardFromDiscardPile()
{
    if (_turnHandler->GetMandatoryColor() != Enums::CardColor::Empty && !_turnHandler->HasCardsStacked())
    {
        ConsoleHelper::PrintMessage(std::format("A Mandatory Color is required For This Turn, Color: {}\n",
            Enums::GetColorDisplayName(_turnHandler->GetMandatoryColor())));
    }

    ConsoleHelper::PrintMessage("Current Top Card is:\n");
    CardDrawHelper::DrawCard(_turnHandler->GetTopCardFromDiscardPile());
}

void Player::DrawCards() const
{
    ConsoleHelper::PrintMessage(std::format("Player {} Hand:\n", GetName()));
    CardDrawHelper::DrawCards(GetCards());
}

bool Player::HasValidCardWithSymbolInHand()
{
    for (const std::shared_ptr<BaseCard>& card : _cardsInHand)
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

bool Player::CardIsCompatible(std::shared_ptr<BaseCard> card)
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

	std::shared_ptr<BaseCard> cardFromDiscardPile = _turnHandler->GetTopCardFromDiscardPile();
	if (card->GetSymbol() == cardFromDiscardPile->GetSymbol())
		return true;
	if (card->GetColor() == cardFromDiscardPile->GetColor())
		return true;

	return false;
}

bool Player::CardIsSymbolOnlyCompatible(std::shared_ptr<BaseCard> card)
{
    std::shared_ptr<BaseCard> cardFromDiscardPile = _turnHandler->GetTopCardFromDiscardPile();
    return card->GetSymbol() == cardFromDiscardPile->GetSymbol();
}

void Player::DispatchWinCondition()
{
	ConsoleHelper::PrintMessage("Victory! Player: " + _name + " Won the Game\n");
	_turnHandler->SetGameState(false);
}

void Player::AddCardToHand(std::shared_ptr<BaseCard> card)
{
	_cardsInHand.emplace_back(card);
}

void Player::HandleYellUnoOption()
{
    if (_cardsInHand.size() <= 2)
    {
        _inUnoState = true;
        ConsoleHelper::PrintMessage("Player: " + _name + " Yelled Uno!\n");
        StartTurn();
    }
    else
    {
        ConsoleHelper::PrintMessage("Can't Yell Uno Yet, Consider Yelling When You Have 2 Cards In Hand\n");
        StartTurn();
    }
}

void Player::HandleBuyCardOption()
{
    _turnHandler->BuyCardsFromDeck(1);
}

void Player::HandleUseCardOption(int option)
{
    std::shared_ptr<BaseCard> currentUseCard;

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
                Enums::GetColorDisplayName(_turnHandler->GetMandatoryColor())));
        }
        else
        {
            ConsoleHelper::PrintMessage("Invalid Action, Please Select a Card With Compatible Symbol or Color\n");
        }

        StartTurn();
    }
}

void Player::HandleWinCondition(const std::shared_ptr<BaseCard> currentUseCard, int option)
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
        TurnEnded();
    }
}

void Player::HandleCardUsage(const std::shared_ptr<BaseCard> currentUseCard, int option)
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

const std::vector<std::shared_ptr<BaseCard>>& Player::GetCards() const
{
	return _cardsInHand;
}

const std::shared_ptr<BaseCard>& Player::GetCard(int index) const
{
    return _cardsInHand[index];
}

void Player::CleanPlayerHand()
{
	_cardsInHand.clear();
}

void Player::ReplaceCardsInHand(const std::vector<std::shared_ptr<BaseCard>>& cards)
{
    _cardsInHand = cards;
}

const std::string& Player::GetName() const
{
	return _name;
}