#pragma once
#include "BaseCard.h"
#include <vector>
#include "DeckData.h"
#include "Enums.h"
#include "PlayersManager.h"

class BaseCard;
class PlayersManager;
class TurnHandler;
class DeckManager
{
private:
	std::shared_ptr<PlayersManager> _playersManager;
	std::vector<std::shared_ptr<BaseCard>> _deck;
	std::vector<std::shared_ptr<BaseCard>> _discardPile;
	std::shared_ptr<TurnHandler> _turnHandler;

public:
	DeckManager(std::shared_ptr<PlayersManager> playersManager);
	void Initialize(std::shared_ptr<TurnHandler> turnHandler);
	void CreateDeck();
	void CreateNumberCards(Enums::CardColor cardColor);
	void CreateJumpCards(Enums::CardColor cardColor);
	void CreateReverseCards(Enums::CardColor cardColor);
	void CreatePlusTwoCards(Enums::CardColor cardColor);
	void ShuffleDeck();
	void ResetAllCards();
	void GetBackPlayerCards();
	void ResetDiscardPile();
	std::shared_ptr<BaseCard> GetTopCardFromDeck();
	std::shared_ptr<BaseCard> BuyTopCardAndRemoveFromDeck();
	void AddCardToDiscardPile(std::shared_ptr<BaseCard> card);
	std::shared_ptr<BaseCard> GetTopCardFromDiscardPile();
	void KeepLastCardAndResetDiscardPile();
	std::shared_ptr<BaseCard> GetFirstNumberCardOnDeckAndRemoveIt();
};

