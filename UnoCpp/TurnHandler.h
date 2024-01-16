#pragma once
#include "BaseCard.h"
#include "BaseAction.h"
#include "DeckManager.h"
#include <vector>

class Player;
class BaseAction;
class DeckManager;
class PlayersManager;
class BaseCard;
class TurnHandler
{
private:
	int _gameDirection = 1;
	int _currentPlayerIndex = 0;
	bool _gameIsRunning = false;
	std::shared_ptr<BaseCard> _throwedCard;
	std::vector<std::shared_ptr<BaseAction>> _actionQueue;
	
	std::vector<std::shared_ptr<BaseCard>> _stackedCardPile;
	std::shared_ptr<DeckManager> _deckManager;
	std::shared_ptr<PlayersManager> _playersManager;
public:
	TurnHandler(std::shared_ptr<DeckManager> deckManager, std::shared_ptr<PlayersManager> playersManager);

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

