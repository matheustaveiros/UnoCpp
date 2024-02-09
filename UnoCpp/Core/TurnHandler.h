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
	
	std::vector<BaseAction*> _actionQueue;
	std::vector<BaseCard*> _stackedCardPile;
	DeckManager* _deckManager;
	PlayersManager* _playersManager;

	const std::string_view _clockwise = "-> Clockwise";
	const std::string_view _counterClockwise = "<- Counter-Clockwise";
public:
	void Initialize(DeckManager* deckManager, PlayersManager* playersManager);
	int GetGameDirection() const;
	std::string_view GetGameDirectionDisplay() const;
	void SetGameState(bool isRunning);
	void ResetState();
	void TurnLoop();
	void AddActionInQueue(BaseAction* action);
	void ExecuteActionInQueue();
	void StartCurrentPlayerTurn();
	void SkipToNextPlayer();
	void ReverseGame();
	void JumpPlayer();
	void AskPlayerToSelectAColor();
	void SetSelectedColor(int selectedColor);
	void DrawCardFromPreviousPlayer();
	void BuyCardsFromDiscardPile(int amount);
	void BuyCardsFromDeck(int amount);
	void BuyCardsAndAddInStackPile(int amount);
	void ApplyStackCardsToPlayer();
	void UseCard(BaseCard* baseCard);
	void SetStarterPlayerOrder(int index);
	void ThrowCardFromDeckToDiscardPile(bool ignoreSpecial);
	void AskForHandToSwap();
	void SwapHand(int selectedPlayer);
	void SetUnoStateIfValid(Player* player) const;
	bool HasValidCard();
	bool IsGameRunning() const;
	bool HasCardsStacked() const;
	Enums::CardColor GetMandatoryColor() const;
	void ResetMandatoryColor();
	BaseCard* GetTopCardFromDiscardPile() const;
	int GetPlayerAmount() const;
	int GetCurrentPlayerIndex() const;
	std::string_view GetPlayerNameByIndex(int index) const;
	int GetPlayerCardAmountById(int index) const;
};

