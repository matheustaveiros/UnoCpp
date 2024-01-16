#include "TurnHandler.h"
#include "Player.h"

TurnHandler::TurnHandler(std::shared_ptr<DeckManager> deckManager, std::shared_ptr<PlayersManager> playersManager) 
    : _deckManager{ deckManager }, _playersManager { playersManager }
{
    
}

int TurnHandler::GetGameDirection()
{
    return _gameDirection;
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
}

void TurnHandler::ReverseGame()
{
    _gameDirection *= -1;
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
        _stackedCardPile.push_back(_deckManager->BuyTopCardAndRemoveFromDeck());
    }
}

void TurnHandler::ApplyStackCardsToPlayer()
{
    std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);
    for (int i = 0; i < _stackedCardPile.size(); i++)
    {
        player->AddCardToHand(_stackedCardPile[i]);
    }

    _stackedCardPile.clear();
}

void TurnHandler::UseCard(std::shared_ptr<BaseCard> baseCard)
{
    std::vector<std::shared_ptr<BaseAction>> cardActions = baseCard->GetActions();
    for (int i = 0; i < cardActions.size(); i++)
    {
        AddActionInQueue(cardActions[i]);
    }

    ExecuteActionInQueue();
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
