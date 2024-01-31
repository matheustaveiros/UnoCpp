#include <format>
#include "Console/ConsoleHelper.h"
#include "Console/CardDrawHelper.h"
#include "Deck/DeckData.h"
#include "Player.h"

Player::Player(std::shared_ptr<TurnHandler> turnHandler, const std::string& name) : _turnHandler{ turnHandler }, _name{ name }
{

}

void Player::StartTurn()
{
    _yellUnoActionValue = -1;
    _buyCardActionValue = -2;
    DrawTopCardFromDiscardPile();
    if (_turnHandler->HasCardsStacked())
    {
        HandleMandatoryPlay();
    }
    else
    {
        DrawCards();
        ShowExtraActions();
        WaitForActionInput();
    }
}

void Player::DrawTopCardFromDiscardPile()
{
    ConsoleHelper::PrintMessage("Current Top Card is:\n");
    CardDrawHelper::DrawCard(_turnHandler->GetTopCardFromDiscardPile());
}

void Player::DrawCards() const
{
	ConsoleHelper::PrintMessage(std::format("Player {} Hand:\n", _name));
	CardDrawHelper::DrawCards(_cardsInHand);
}

void Player::ShowExtraActions()
{
	int startOffset = static_cast<int>(_cardsInHand.size());
	_buyCardActionValue = startOffset;
	_yellUnoActionValue = startOffset + 1;

	ConsoleHelper::PrintMessage("Type Any Card Id to Use Or\n");
    ConsoleHelper::PrintMessage(std::format("Type {} to Buy One Card\n", _buyCardActionValue));
    ConsoleHelper::PrintMessage(std::format("Type {} to Yell Uno!\n", _yellUnoActionValue));
}

void Player::WaitForActionInput()
{
	int selectedAction = ConsoleHelper::GetInput<int>("Insert the number of the action to Play: \n");
	UseOption(selectedAction);
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
            ConsoleHelper::PrintMessage(std::format("A Mandatory Color is required For This Turn, Color: {}\n", 
                Enums::GetColorDisplayName(_turnHandler->GetMandatoryColor())));
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

void Player::HandleMandatoryPlay()
{
    ConsoleHelper::Clear();
    DrawTopCardFromDiscardPile();
    DrawCards();

    std::shared_ptr<BaseCard> topCard = _turnHandler->GetTopCardFromDiscardPile();
    ConsoleHelper::PrintMessage("Mandatory Use of Special Card Type: " + topCard->GetSymbol() + "\n");

    ShowCompatibleOptions();
}

void Player::ShowCompatibleOptions()
{
    std::vector<int> validCards;
    std::string displayText = "Select the Following Options to Play: ";
    for (int i = 0; i < _cardsInHand.size(); i++)
    {
        std::shared_ptr<BaseCard> handCard = _cardsInHand[i];
        if (CardIsSymbolOnlyCompatible(handCard))
        {
            displayText += std::format("({}) ", i);
            validCards.emplace_back(i);
        }
    }

    if (validCards.empty())
    {
        ConsoleHelper::PrintMessage("No Valid Plays\n");
        _turnHandler->ApplyStackCardsToPlayer();
        _turnHandler->SkipToNextPlayer();
    }
    else
    {
        displayText += "\n";

        int selectedAction = ConsoleHelper::GetInput<int>(displayText);
        for(const int& cardNumber : validCards)
        {
            if (selectedAction == cardNumber)
            {
                UseOption(selectedAction);
                break;
            }
        }
    }
}

void Player::UseOption(int option)
{
    ConsoleHelper::Clear();

    if (option == _yellUnoActionValue)
    {
        HandleYellUnoOption();
    }
    else if (option == _buyCardActionValue)
    {
        HandleBuyCardOption();
    }
    else
    {
        HandleUseCardOption(option);
    }
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

    if(option < _cardsInHand.size())
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
        ConsoleHelper::PrintMessage("Invalid Action, Please Select a Card With Compatible Symbol or Color\n");
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