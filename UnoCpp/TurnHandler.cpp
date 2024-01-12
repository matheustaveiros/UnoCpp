#include "TurnHandler.h"
#include "Player.h"

TurnHandler::TurnHandler(std::shared_ptr<DeckManager> deckManager)
{
    _deckManager = deckManager;
}

int TurnHandler::GetGameDirection()
{
    return _gameDirection;
}

void TurnHandler::TurnLoop()
{
    StartCurrentPlayerTurn();
}

void TurnHandler::AddActionInQueue(BaseAction& action)
{
    _actionQueue.push_back(action);
}

void TurnHandler::RemoveActionFromQueue(BaseAction& action)
{
}

void TurnHandler::ExecuteActionInQueue()
{
    while (!_actionQueue.empty())
    {
        BaseAction& action = _actionQueue[0];
        action.Execute();
        _actionQueue.erase(_actionQueue.begin());
    }
}

void TurnHandler::StartCurrentPlayerTurn()
{
    Player& player = _players[_currentPlayerIndex];
    player.StartTurn();
}

void TurnHandler::SkipToNextPlayer()
{
    _currentPlayerIndex += _gameDirection;
    if (_currentPlayerIndex >= _players.size())
    {
        _currentPlayerIndex = 0;
    }
    else if (_currentPlayerIndex < 0) {
        _currentPlayerIndex = _players.size() - 1;
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
    Player& player = _players[_currentPlayerIndex];
    for (int i = 0; i < _stackedCardPile.size(); i++)
    {
        player.AddCardToHand(_stackedCardPile[i]);
    }

    _stackedCardPile.clear();
}

void TurnHandler::UseCard(BaseCard& baseCard)
{
    std::vector<BaseAction> cardActions = baseCard.GetActions();
    for (int i = 0; i < cardActions.size(); i++)
    {
        AddActionInQueue(cardActions[i]);
    }

    ExecuteActionInQueue();
}

bool TurnHandler::HasValidCard()
{
    Player& player = _players[_currentPlayerIndex];
    return player.HasValidActions(*_throwedCard);
}

bool TurnHandler::IsGameRunning()
{
    return _gameIsRunning;
}
