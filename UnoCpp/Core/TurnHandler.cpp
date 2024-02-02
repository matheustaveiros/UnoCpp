#include <format>
#include "Player/Player.h"
#include "Console/ConsoleHelper.h"
#include "Console/CardDrawHelper.h"
#include "TurnHandler.h"

void TurnHandler::Initialize(std::shared_ptr<DeckManager> deckManager, std::shared_ptr<PlayersManager> playersManager)
{
    _deckManager = deckManager;
    _playersManager = playersManager;
}

int TurnHandler::GetGameDirection() const
{
    return _gameDirection;
}

const std::string& TurnHandler::GetGameDirectionDisplay() const
{
    return _gameDirection == 1 ? _clockwise : _counterClockwise;
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
    _actionQueue.emplace_back(action);
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
    ConsoleHelper::PrintMessage("Game Order Changed, Now is: " + GetGameDirectionDisplay() + "\n", Enums::CardColor::Yellow);
    SkipToNextPlayer();
}

void TurnHandler::JumpPlayer()
{
    SkipToNextPlayer();
    SkipToNextPlayer();
}

void TurnHandler::AskPlayerToSelectAColor()
{
    _playersManager->GetPlayer(_currentPlayerIndex)->AskToSelectAColor();
}

void TurnHandler::SetSelectedColor(int selectedColor)
{
    _mandatoryColor = static_cast<Enums::CardColor>(selectedColor);
    ConsoleHelper::PrintMessage(std::format("Player {} Selected a Mandatory Color: {}\n", 
        _playersManager->GetPlayer(_currentPlayerIndex)->GetName(), Enums::GetColorDisplayName(_mandatoryColor)), _mandatoryColor);
}

void TurnHandler::DrawCardFromPreviousPlayer()
{
    int playerIndex = _currentPlayerIndex;
    playerIndex += -_gameDirection;
    int playerAmount = static_cast<int>(_playersManager->GetPlayers().size());

    if (playerIndex < 0)
        playerIndex = playerAmount - 1;
    else if (playerIndex >= playerAmount)
        playerIndex = 0;

    CardDrawHelper::DrawCards(_playersManager->GetPlayer(playerIndex)->GetCards());
}

void TurnHandler::BuyCardsFromDiscardPile(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        _stackedCardPile.emplace_back(_deckManager->BuyTopCardAndRemoveFromDiscardPile());
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
        _stackedCardPile.emplace_back(_deckManager->BuyTopCardAndRemoveFromDeck());
    }

    ConsoleHelper::PrintMessage(std::format("{} Cards Added to Stack Pile\n", amount));
}

void TurnHandler::ApplyStackCardsToPlayer()
{
    std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);
    for (const std::shared_ptr<BaseCard>& card : _stackedCardPile)
    {
        player->AddCardToHand(card);
    }

    ConsoleHelper::PrintMessage(std::format("Stack Pile(cards: {})\nThe Cards Will Be Applied to Player: {} Hand\n", _stackedCardPile.size(), player->GetName()), Enums::CardColor::Red);
    _stackedCardPile.clear();
}

void TurnHandler::UseCard(std::shared_ptr<BaseCard> baseCard)
{
    for (const std::shared_ptr<BaseAction>& card : baseCard->GetActions())
    {
        AddActionInQueue(card);
    }

    _deckManager->AddCardToDiscardPile(baseCard);

    ConsoleHelper::PrintMessage(std::format("Card Used by {}: \n", _playersManager->GetPlayer(_currentPlayerIndex)->GetName()));
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

void TurnHandler::AskForHandToSwap()
{
    _playersManager->GetPlayer(_currentPlayerIndex)->AskForHandToSwap();
}

void TurnHandler::SwapHand(int selectedPlayer)
{
    std::shared_ptr<Player> playerA = _playersManager->GetPlayer(_currentPlayerIndex);
    std::shared_ptr<Player> playerB = _playersManager->GetPlayer(selectedPlayer);
    std::vector<std::shared_ptr<BaseCard>> playerACards = playerA->GetCards();
    std::vector<std::shared_ptr<BaseCard>> playerBCards = playerB->GetCards();

    playerA->ReplaceCardsInHand(playerBCards);
    playerB->ReplaceCardsInHand(playerACards);

    SetUnoStateIfValid(playerA);
    SetUnoStateIfValid(playerB);

    ConsoleHelper::PrintMessage(std::format("Players Hands Swapped Player: {} With Player: {}\n", playerA->GetName(), playerB->GetName()), Enums::CardColor::Yellow);
}

void TurnHandler::SetUnoStateIfValid(std::shared_ptr<Player> player) const
{
    if (player->GetCards().size() <= 1)
    {
        player->SetUnoState(true);
        ConsoleHelper::PrintMessage(std::format("Player: {} Has Yelled Uno!\n", player->GetName()), Enums::CardColor::Yellow);
    }
}

bool TurnHandler::HasValidCard()
{
    std::shared_ptr<Player> player = _playersManager->GetPlayer(_currentPlayerIndex);
    return player->HasValidCardWithSymbolInHand();
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

int TurnHandler::GetPlayerAmount()
{
    return static_cast<int>(_playersManager->GetPlayers().size());
}

int TurnHandler::GetCurrentPlayerIndex()
{
    return _currentPlayerIndex;
}

const std::string& TurnHandler::GetPlayerNameByIndex(int index) const
{
    return _playersManager->GetPlayer(index)->GetName();
}

const int TurnHandler::GetPlayerCardAmountById(int index) const
{
    return static_cast<int>(_playersManager->GetPlayer(index)->GetCards().size());
}
