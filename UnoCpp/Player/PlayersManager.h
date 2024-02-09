#pragma once
#include <vector>
#include <memory>
#include <string>
#include <span>

class Player;
class TurnHandler;
class DeckManager;
class PlayersManager
{
private:
	std::vector<std::unique_ptr<Player>> _players;
	TurnHandler* _turnHandler;
	DeckManager* _deckManager;

public:
	void Initialize(TurnHandler* turnHandler, DeckManager* deckManager);
	std::span<Player*> GetPlayers() const;
	Player* GetPlayer(int index);
	void CreatePlayers(int amount, const std::span<std::string_view> playerNames);
	void CreateBots(int amount, const std::span<std::string_view> playerNames);
	void DestroyAllPlayers();
	void GiveFirstCardsToPlayers();
};

