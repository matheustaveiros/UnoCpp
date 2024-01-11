#pragma once
#include "BaseCard.h"
#include <list>
#include "DeckData.h"
class DeckManager
{
private:
	std::list<BaseCard> _cards;
	std::list<BaseCard> _discardPile;

public:
	void CreateDeck();
	void ShuffleDeck();
	void ResetDeck();
	void GetBackPlayerCards(/*Player[] player*/);
	BaseCard GetTopCard();
};

