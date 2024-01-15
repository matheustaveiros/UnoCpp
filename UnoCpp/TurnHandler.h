#pragma once
#include "BaseCard.h"
#include "BaseAction.h"
#include "Player.h"
#include "DeckManager.h"
#include <vector>

class Player;
class BaseAction;
class DeckManager;
class TurnHandler
{
private:
	int _gameDirection;
	int _currentPlayerIndex;
	bool _gameIsRunning;
	std::shared_ptr<BaseCard> _throwedCard;
	std::vector<std::shared_ptr<BaseAction>> _actionQueue;
	std::vector<std::shared_ptr<Player>> _players;
	std::vector<std::shared_ptr<BaseCard>> _stackedCardPile;
	std::shared_ptr<DeckManager> _deckManager;
public:
	explicit TurnHandler(std::shared_ptr<DeckManager> deckManager);

	int GetGameDirection();
	void TurnLoop();
	void AddActionInQueue(std::shared_ptr<BaseAction> action);
	void RemoveActionFromQueue(std::shared_ptr<BaseAction> action);
	void ExecuteActionInQueue();
	void StartCurrentPlayerTurn();
	void SkipToNextPlayer();
	void ReverseGame();
	void JumpPlayer();
	void BuyCardsFromDeck(int amount);
	void ApplyStackCardsToPlayer();
	void UseCard(std::shared_ptr<BaseCard> baseCard);
	bool HasValidCard();
	bool IsGameRunning();
};

