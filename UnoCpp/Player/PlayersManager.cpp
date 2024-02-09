#include "Deck/DeckData.h"
#include "Console/ConsoleHelper.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Utils/PointerHelper.h"
#include "PlayersManager.h"

void PlayersManager::Initialize(TurnHandler* turnHandler, DeckManager* deckManager)
{
    _turnHandler = turnHandler;
    _deckManager = deckManager;
}

std::span<Player*> PlayersManager::GetPlayers() const
{
    return PointerHelper::GetPointersSpan(_players);
}

Player* PlayersManager::GetPlayer(int index)
{
    if (_players.empty() || index >= _players.size())
        return nullptr;

    return _players[index].get();
}

void PlayersManager::CreatePlayers(int amount, const std::span<std::string_view> playerNames)
{
    for (int i = 0; i < amount; i++)
    {
        auto newPlayer = std::make_unique<HumanPlayer>(_turnHandler, playerNames[i]);
        _players.emplace_back(newPlayer);
    }
}

void PlayersManager::CreateBots(int amount, const std::span<std::string_view> playerNames)
{
    for (int i = 0; i < amount; i++)
    {
        auto newPlayer = std::make_unique<AIPlayer>(_turnHandler, playerNames[i]);
        _players.emplace_back(newPlayer);
    }
}

void PlayersManager::DestroyAllPlayers()
{
    _players.clear();
}

void PlayersManager::GiveFirstCardsToPlayers()
{
    for (const std::unique_ptr<Player>& player : _players)
    {
        for (int cardsIndex = 0; cardsIndex < DeckData::AMOUNT_OF_INITIAL_CARDS; cardsIndex++)
        {
            BaseCard* card = _deckManager->BuyTopCardAndRemoveFromDeck();
            player->AddCardToHand(card);
        }
    }

    ConsoleHelper::PrintMessage("All players Received Initial Cards\n", Enums::CardColor::Empty, Enums::DisplayLevel::Developer);
}
