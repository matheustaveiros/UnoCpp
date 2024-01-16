#include "PlayersManager.h"
#include "Player.h"

void PlayersManager::Initialize(std::shared_ptr<TurnHandler> turnHandler)
{
    _turnHandler = turnHandler;
}

std::vector<std::shared_ptr<Player>> PlayersManager::GetPlayers()
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
}

