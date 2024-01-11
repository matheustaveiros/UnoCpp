#pragma once
#include <vector>
#include "BaseAction.h"
#include "Player.h"
#include "BaseCard.h"
#include "DeckManager.h"
class TurnHandler
{
private:
	int _gameDirection;
	int _currentPlayerIndex;
	bool _gameIsRunning;
	BaseCard& _throwedCard;
	std::vector<BaseAction> _actionQueue;
	std::vector<Player> _players;
	std::vector<BaseCard> _stackedCardPile;
	DeckManager _deckManager;
public:
	TurnHandler(const DeckManager& deckManager) {
		_deckManager = deckManager;
	};

	int GetGameDirection();
	void TurnLoop();
	void AddActionInQueue(BaseAction& action);
	void RemoveActionFromQueue(BaseAction& action);
	void ExecuteActionInQueue();
	void StartCurrentPlayerTurn();
	void SkipToNextPlayer();
	void ReverseGame();
	void JumpPlayer();
	void BuyCardsFromDeck(int amount);
	void ApplyStackCardsToPlayer();
	void UseCard(BaseCard& baseCard);
	bool HasValidCard();
	bool IsGameRunning();
};

