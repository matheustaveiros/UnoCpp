#pragma once
#include "BaseCard.h"
#include <vector>
#include "DeckData.h"
#include "Enums.h"
#include "PlayersManager.h"

class BaseCard;
class PlayersManager;
class DeckManager
{
private:
	std::shared_ptr<PlayersManager> _playersManager;
	std::vector<std::shared_ptr<BaseCard>> _cards;
	std::vector<std::shared_ptr<BaseCard>> _discardPile;

public:
	DeckManager(std::shared_ptr<PlayersManager> playersManager);
	void CreateDeck();
	void CreateNumberCards(Enums::CardColor cardColor);
	void CreateJumpCards(Enums::CardColor cardColor);
	void CreateReverseCards(Enums::CardColor cardColor);
	void CreatePlusTwoCards(Enums::CardColor cardColor);
	void ShuffleDeck();
	void ResetDeck();
	void GetBackPlayerCards();
	std::shared_ptr<BaseCard> GetTopCardFromDeck();
	std::shared_ptr<BaseCard> BuyTopCardAndRemoveFromDeck();
	void AddCardToDiscardPile(std::shared_ptr<BaseCard> card);
	std::shared_ptr<BaseCard> GetTopCardFromDiscardPile();
};

