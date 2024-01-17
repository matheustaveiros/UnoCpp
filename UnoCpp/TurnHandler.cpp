#include "TurnHandler.h"
#include "Player.h"
#include "ConsoleHelper.h"
#include "CardDrawHelper.h"

TurnHandler::TurnHandler(std::shared_ptr<DeckManager> deckManager, std::shared_ptr<PlayersManager> playersManager) 
    : _deckManager{ deckManager }, _playersManager { playersManager }
{
    
}

int TurnHandler::GetGameDirection()
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

void TurnHandler::TurnLoop()
{
    StartCurrentPlayerTurn();
}

void TurnHandler::AddActionInQueue(std::shared_ptr<BaseAction> action)
{
    _actionQueue.push_back(action);
}

void TurnHandler::RemoveActionFromQueue(std::shared_ptr<BaseAction> action)
{
}

void TurnHandler::ExecuteActionInQueue()
{
    while (!_actionQueue.empty())
    {
        std::shared_ptr<BaseAction> action = _actionQueue[0];
        action->Execute();
        _actionQueue.erase(_actionQueue.begin());
    }
}

void TurnHandler::StartCurrentPlayerTurn()
{
    std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);

    ConsoleHelper::PrintMessage("Turn Started, Current Player is: " + player->GetName() + "\n");
    ConsoleHelper::PrintMessage("Current Top Card is:\n");

    CardDrawHelper::DrawCard(GetTopCardFromDiscardPile());

    player->StartTurn();
}

void TurnHandler::SkipToNextPlayer()
{
    _currentPlayerIndex += _gameDirection;
    if (_currentPlayerIndex >= _playersManager->GetPlayers().size())
    {
        _currentPlayerIndex = 0;
    }
    else if (_currentPlayerIndex < 0) {
        _currentPlayerIndex = _playersManager->GetPlayers().size() - 1;
    }

    ConsoleHelper::PrintMessage("Player Skipped\n");
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

void TurnHandler::BuyCardsFromDeck(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        std::shared_ptr<BaseCard> grabbedCard = _deckManager->BuyTopCardAndRemoveFromDeck();

        std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);
        player->AddCardToHand(_stackedCardPile[i]);
    }

    ConsoleHelper::PrintMessage(std::to_string(amount) + "Cards Bought\n");
}


void TurnHandler::BuyCardsFromStackPile(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        _stackedCardPile.push_back(_deckManager->BuyTopCardAndRemoveFromDeck());
    }

    ConsoleHelper::PrintMessage(std::to_string(amount) + "Cards Bought\n");
}

void TurnHandler::ApplyStackCardsToPlayer()
{
    std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);
    for (int i = 0; i < _stackedCardPile.size(); i++)
    {
        player->AddCardToHand(_stackedCardPile[i]);
    }

    ConsoleHelper::PrintMessage("Stack Pile(cards: " + std::to_string(_stackedCardPile.size()) + ") applied to" + player->GetName() + " hand\n");
    _stackedCardPile.clear();
}

void TurnHandler::UseCard(std::shared_ptr<BaseCard> baseCard)
{
    std::vector<std::shared_ptr<BaseAction>> cardActions = baseCard->GetActions();
    for (int i = 0; i < cardActions.size(); i++)
    {
        AddActionInQueue(cardActions[i]);
    }

    ConsoleHelper::PrintMessage("Card Used: \n");
    CardDrawHelper::DrawCard(baseCard);

    ExecuteActionInQueue();
}

void TurnHandler::SetStarterPlayerOrder(int index)
{
    _currentPlayerIndex = index;
}

void TurnHandler::ThrowCardFromDeckToDiscardPile()
{
    std::shared_ptr<BaseCard> deckCard = _deckManager->BuyTopCardAndRemoveFromDeck();
    _deckManager->AddCardToDiscardPile(deckCard);
}

bool TurnHandler::HasValidCard()
{
    std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);
    return player->HasValidActions(_throwedCard);
}

bool TurnHandler::IsGameRunning()
{
    return _gameIsRunning;
}

std::shared_ptr<BaseCard> TurnHandler::GetTopCardFromDiscardPile()
{
    return _deckManager->GetTopCardFromDiscardPile();
}
