#pragma once
#include "BaseCard.h"
#include <vector>
#include "DeckData.h"
class DeckManager
{
private:
	std::vector<BaseCard> _cards;
	std::vector<BaseCard> _discardPile;

public:
	void CreateDeck();
	void ShuffleDeck();
	void ResetDeck();
	void GetBackPlayerCards(/*Player[] player*/);
	BaseCard& GetTopCard();
	BaseCard& BuyTopCardAndRemoveFromDeck();
};

