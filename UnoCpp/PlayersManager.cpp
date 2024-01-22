#include "PlayersManager.h"
#include "Player.h"
#include "DeckData.h"
#include "ConsoleHelper.h"

void PlayersManager::Initialize(std::shared_ptr<TurnHandler> turnHandler, std::shared_ptr<DeckManager> deckManager)
{
    _turnHandler = turnHandler;
    _deckManager = deckManager;
}

std::vector<std::shared_ptr<Player>> PlayersManager::GetPlayers() const
{
    return _players;
}

std::shared_ptr<Player> PlayersManager::GetPlayer(int index)
{
    if (_players.empty() || index >= _players.size())
        return nullptr;

    return _players[index];
}

void PlayersManager::CreatePlayers(int amount, std::vector<std::string> playerNames)
{
    for (int i = 0; i < amount; i++)
    {
        std::shared_ptr<Player> newPlayer = std::make_shared<Player>(_turnHandler, playerNames[i]);
        _players.push_back(newPlayer);
    }
}

void PlayersManager::DestroyAllPlayers()
{
    _players.clear();
}

void PlayersManager::GiveFirstCardsToPlayers()
{
    for (int playerIndex = 0; playerIndex < _players.size(); playerIndex++)
    {
        for (int cardsIndex = 0; cardsIndex < DeckData::AMOUNT_OF_INITIAL_CARDS; cardsIndex++)
        {
            std::shared_ptr<BaseCard> card = _deckManager->BuyTopCardAndRemoveFromDeck();
            _players[playerIndex]->AddCardToHand(card);
        }
    }

    ConsoleHelper::PrintMessage("All players Received Initial Cards\n", Enums::DisplayLevel::Developer);
}
