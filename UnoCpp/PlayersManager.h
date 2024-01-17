#pragma once
#include <vector>
#include <memory>
#include <string>

class Player;
class TurnHandler;
class DeckManager;
class PlayersManager
{
private:
	std::vector<std::shared_ptr<Player>> _players;
	std::shared_ptr<TurnHandler> _turnHandler;
	std::shared_ptr<DeckManager> _deckManager;

public:
	void Initialize(std::shared_ptr<TurnHandler> turnHandler, std::shared_ptr<DeckManager> deckManager);
	std::vector<std::shared_ptr<Player>> GetPlayers();
	std::shared_ptr<Player> GetPlayer(int index);
	void CreatePlayers(int amount, std::vector<std::string> playerNames);
	void DestroyAllPlayers();
	void GiveFirstCardsToPlayers();
};

