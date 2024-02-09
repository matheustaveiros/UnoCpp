#pragma once
#include <vector>
#include "Cards/BaseCard.h"
#include "Utils/Enums.h"
#include "Player/PlayersManager.h"
#include "DeckData.h"

class BaseCard;
class PlayersManager;
class TurnHandler;
class DeckManager
{
private:
	TurnHandler* _turnHandler;
	PlayersManager* _playersManager;
	std::vector<std::unique_ptr<BaseCard>> _deck;
	std::vector<BaseCard*> _discardPile;

public:
	void Initialize(TurnHandler* turnHandler, PlayersManager* playersManager);
	void CreateDeck();
	void CreateNumberCards(Enums::CardColor cardColor);
	void CreateJumpCards(Enums::CardColor cardColor);
	void CreateReverseCards(Enums::CardColor cardColor);
	void CreatePlusTwoCards(Enums::CardColor cardColor);
	void CreateSwapHandsCards(Enums::CardColor cardColor);
	void CreateBuyFromDiscardPileCards(Enums::CardColor cardColor);
	void CreatePlusFourCards(Enums::CardColor cardColor);
	void CreateChooseColorCards(Enums::CardColor cardColor);
	void ShuffleDeck();
	void ResetAllCards();
	void GetBackPlayerCards();
	void ResetDiscardPile();
	BaseCard* GetTopCardFromDeck();
	BaseCard* BuyTopCardAndRemoveFromDeck();
	void AddCardToDiscardPile(BaseCard* card);
	BaseCard* BuyTopCardAndRemoveFromDiscardPile();
	BaseCard* GetTopCardFromDiscardPile();
	void KeepLastCardAndResetDiscardPile();
	BaseCard* GetFirstNumberCardOnDeckAndRemoveIt();
};

