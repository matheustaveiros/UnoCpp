#include "TurnHandler.h"
#include "Player.h"
#include "ConsoleHelper.h"
#include "CardDrawHelper.h"
#include <format>

TurnHandler::TurnHandler(std::shared_ptr<DeckManager> deckManager, std::shared_ptr<PlayersManager> playersManager) 
    : _deckManager{ deckManager }, _playersManager { playersManager }
{
    
}

int TurnHandler::GetGameDirection() const
{
    return _gameDirection;
}

std::string TurnHandler::GetGameDirectionDisplay() const
{
    const std::string clockwise = "� Clockwise";
    const std::string counterClockwise = "� counter-clockwise";

    return _gameDirection == 1 ? clockwise : counterClockwise;
}

void TurnHandler::SetGameState(bool isRunning)
{
    _gameIsRunning = isRunning;
}

void TurnHandler::ResetState()
{
    _gameIsRunning = false;
    _gameDirection = 1;
    _currentPlayerIndex = 0;
}

void TurnHandler::TurnLoop()
{
    StartCurrentPlayerTurn();
}

void TurnHandler::AddActionInQueue(std::shared_ptr<BaseAction> action)
{
    _actionQueue.push_back(action);
}

void TurnHandler::ExecuteActionInQueue()
{
    while (!_actionQueue.empty())
    {
        std::shared_ptr<BaseAction> action = _actionQueue.front();
        action->Execute();
        _actionQueue.erase(_actionQueue.begin());
    }
}

void TurnHandler::StartCurrentPlayerTurn()
{
    std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);

    ConsoleHelper::PrintMessage("Turn Started, Current Player is: " + player->GetName() + "\n");

    player->StartTurn();
}

void TurnHandler::SkipToNextPlayer()
{
    _currentPlayerIndex += _gameDirection;
    if (_currentPlayerIndex >= static_cast<int>(_playersManager->GetPlayers().size()))
    {
        _currentPlayerIndex = 0;
    }
    else if (_currentPlayerIndex < 0)
    {
        _currentPlayerIndex = static_cast<int>(_playersManager->GetPlayers().size()) - 1;
    }

    ConsoleHelper::PrintMessage("Player Changed\n");
}

void TurnHandler::ReverseGame()
{
    _gameDirection *= -1;
    ConsoleHelper::PrintMessage("Game Order Changed, Now is: " + GetGameDirectionDisplay() + "\n");
    SkipToNextPlayer();
}

void TurnHandler::JumpPlayer()
{
    SkipToNextPlayer();
    SkipToNextPlayer();
}

void TurnHandler::AskPlayerToSelectAColor()
{
    int selectedColor = ConsoleHelper::GetInput<int>(std::format("Please Select a Color By Number For The Next Play: Blue ({}), Green ({}), Red ({}), Yellow ({})\n", 
        static_cast<int>(Enums::CardColor::Blue), static_cast<int>(Enums::CardColor::Green), static_cast<int>(Enums::CardColor::Red), static_cast<int>(Enums::CardColor::Yellow)));
    if (selectedColor <= 0 || selectedColor > 4)
    {
        ConsoleHelper::PrintMessage(std::format("Invalid Input, Please Select a Valid Number ({}, {}, {}, {})\n",
            static_cast<int>(Enums::CardColor::Blue), static_cast<int>(Enums::CardColor::Green), static_cast<int>(Enums::CardColor::Red), static_cast<int>(Enums::CardColor::Yellow)));
        AskPlayerToSelectAColor();
    }
    else
    {
        _mandatoryColor = static_cast<Enums::CardColor>(selectedColor);
        ConsoleHelper::Clear();
        ConsoleHelper::PrintMessage(std::format("Current Selected Mandatory Color: {}\n", Enums::GetColorDisplayName(_mandatoryColor)));
    }
}

void TurnHandler::BuyCardsFromDeck(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        std::shared_ptr<BaseCard> grabbedCard = _deckManager->BuyTopCardAndRemoveFromDeck();

        std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);
        player->AddCardToHand(grabbedCard);
    }

    ConsoleHelper::PrintMessage(std::format("{} Cards Bought\n", amount));
}


void TurnHandler::BuyCardsAndAddInStackPile(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        _stackedCardPile.push_back(_deckManager->BuyTopCardAndRemoveFromDeck());
    }

    ConsoleHelper::PrintMessage(std::format("{} Cards Added to Stack Pile\n", amount));
}

void TurnHandler::ApplyStackCardsToPlayer()
{
    std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);
    for (int i = 0; i < _stackedCardPile.size(); i++)
    {
        player->AddCardToHand(_stackedCardPile[i]);
    }

    ConsoleHelper::PrintMessage(std::format("Stack Pile(cards: {}) Applied to Player: {} Hand\n", _stackedCardPile.size(), player->GetName()));
    _stackedCardPile.clear();
}

void TurnHandler::UseCard(std::shared_ptr<BaseCard> baseCard)
{
    std::vector<std::shared_ptr<BaseAction>> cardActions = baseCard->GetActions();
    for (int i = 0; i < cardActions.size(); i++)
    {
        AddActionInQueue(cardActions[i]);
    }

    _deckManager->AddCardToDiscardPile(baseCard);

    ConsoleHelper::PrintMessage("Card Used: \n");
    CardDrawHelper::DrawCard(baseCard);

    ExecuteActionInQueue();
}

void TurnHandler::SetStarterPlayerOrder(int index)
{
    _currentPlayerIndex = index;
}

void TurnHandler::ThrowCardFromDeckToDiscardPile(bool ignoreSpecial)
{
    std::shared_ptr<BaseCard> selectedCard;
    if (ignoreSpecial)
    {
        selectedCard = _deckManager->GetFirstNumberCardOnDeckAndRemoveIt();
    }
    else
    {
        selectedCard = _deckManager->BuyTopCardAndRemoveFromDeck();
    }

    _deckManager->AddCardToDiscardPile(selectedCard);
}

bool TurnHandler::HasValidCard()
{
    std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);
    return player->HasValidActions(_deckManager->GetTopCardFromDiscardPile());
}

bool TurnHandler::IsGameRunning() const
{
    return _gameIsRunning;
}

bool TurnHandler::HasCardsStacked() const
{
    return _stackedCardPile.empty() == false;
}

Enums::CardColor TurnHandler::GetMandatoryColor() const
{
    return _mandatoryColor;
}

void TurnHandler::ResetMandatoryColor()
{
    _mandatoryColor = Enums::CardColor::Empty;
}

std::shared_ptr<BaseCard> TurnHandler::GetTopCardFromDiscardPile()
{
    return _deckManager->GetTopCardFromDiscardPile();
}
