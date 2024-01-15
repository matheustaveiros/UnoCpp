#pragma once
#include "BaseCard.h"
#include <vector>
#include "DeckData.h"
class BaseCard;
class DeckManager
{
private:
	std::vector<std::shared_ptr<BaseCard>> _cards;
	std::vector<std::shared_ptr<BaseCard>> _discardPile;

public:
	void CreateDeck();
	void ShuffleDeck();
	void ResetDeck();
	void GetBackPlayerCards();
	std::shared_ptr<BaseCard> GetTopCard();
	std::shared_ptr<BaseCard> BuyTopCardAndRemoveFromDeck();
};

