#include "Player.h"
#include "ConsoleHelper.h"
#include "CardDrawHelper.h"
#include "DeckData.h"

void Player::StartTurn()
{
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

Player::Player(std::shared_ptr<TurnHandler> turnHandler, std::string name) : _turnHandler{ turnHandler }, _name{ name }
{

}

void Player::DrawTopCardFromDiscardPile()
{
    ConsoleHelper::PrintMessage("Current Top Card is:\n");
    CardDrawHelper::DrawCard(_turnHandler->GetTopCardFromDiscardPile());
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
			if (CardIsSymbolOnlyCompatible(_cardsInHand[i]))
				return true;
		}
	}
	else
    {
		for (int i = 0; i < _cardsInHand.size(); i++)
		{
			if (CardIsCompatible(_cardsInHand[i]))
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

bool Player::CardIsSymbolOnlyCompatible(std::shared_ptr<BaseCard> card)
{
    std::shared_ptr<BaseCard> cardFromDiscardPile = _turnHandler->GetTopCardFromDiscardPile();
    if (card->GetSymbol() == cardFromDiscardPile->GetSymbol())
        return true;

    return false;
}

void Player::DispatchWinCondition()
{
	ConsoleHelper::PrintMessage("Victory! Player: " + _name + " Won the Game\n");
	_turnHandler->SetGameState(false);
}

void Player::AddCardToHand(std::shared_ptr<BaseCard> card)
{
	_cardsInHand.push_back(card);
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
            displayText += std::to_string(i) + ", ";
            validCards.push_back(i);
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
        for (int i = 0; i < validCards.size(); i++)
        {
            if (selectedAction == validCards[i])
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