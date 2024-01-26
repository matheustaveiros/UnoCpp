#pragma once
#include <vector>
#include "Cards/BaseCard.h"
#include "Actions/BaseAction.h"
#include "Deck/DeckManager.h"

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
	Enums::CardColor _mandatoryColor = Enums::CardColor::Empty;
	
	std::vector<std::shared_ptr<BaseAction>> _actionQueue;
	std::vector<std::shared_ptr<BaseCard>> _stackedCardPile;
	std::shared_ptr<DeckManager> _deckManager;
	std::shared_ptr<PlayersManager> _playersManager;
public:
	void Initialize(std::shared_ptr<DeckManager> deckManager, std::shared_ptr<PlayersManager> playersManager);
	int GetGameDirection() const;
	std::string GetGameDirectionDisplay() const;
	void SetGameState(bool isRunning);
	void ResetState();
	void TurnLoop();
	void AddActionInQueue(std::shared_ptr<BaseAction> action);
	void ExecuteActionInQueue();
	void StartCurrentPlayerTurn();
	void SkipToNextPlayer();
	void ReverseGame();
	void JumpPlayer();
	void AskPlayerToSelectAColor();
	void DrawCardFromPreviousPlayer();
	void BuyCardsFromDiscardPile(int amount);
	void BuyCardsFromDeck(int amount);
	void BuyCardsAndAddInStackPile(int amount);
	void ApplyStackCardsToPlayer();
	void UseCard(std::shared_ptr<BaseCard> baseCard);
	void SetStarterPlayerOrder(int index);
	void ThrowCardFromDeckToDiscardPile(bool ignoreSpecial);
	void AskForHandToSwap();
	void SwapHand(int selectedPlayer);
	bool HasValidCard();
	bool IsGameRunning() const;
	bool HasCardsStacked() const;
	Enums::CardColor GetMandatoryColor() const;
	void ResetMandatoryColor();
	std::shared_ptr<BaseCard> GetTopCardFromDiscardPile();
};

