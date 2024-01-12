#pragma once
#include <vector>
#include "BaseCard.h"
#include "BaseAction.h"
#include "DeckManager.h"

class Player;
class TurnHandler
{
private:
	int _gameDirection;
	int _currentPlayerIndex;
	bool _gameIsRunning;
	BaseCard* _throwedCard;
	std::vector<BaseAction> _actionQueue;
	std::vector<Player> _players;
	std::vector<BaseCard> _stackedCardPile;
	std::shared_ptr<DeckManager> _deckManager;
public:
	explicit TurnHandler(std::shared_ptr<DeckManager> deckManager);

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

