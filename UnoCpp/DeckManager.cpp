#include "DeckManager.h"
#include "DeckData.h"
#include "NumberCard.h"
#include "JumpCard.h"
#include "ReverseCard.h"
#include "PlusTwoCard.h"

void DeckManager::CreateDeck()
{
	std::vector<Enums::CardColor> colorList{ Enums::Blue, Enums::Green, Enums::Red, Enums::Yellow };

	for (int i = 0; i < colorList.size(); i++)
	{
		Enums::CardColor cardColor = colorList[i];
		CreateNumberCards(cardColor);
		CreateJumpCards(cardColor);
		CreateReverseCards(cardColor);
		CreatePlusTwoCards(cardColor);
	}
}

void DeckManager::CreateNumberCards(Enums::CardColor cardColor)
{
	for (int cardByColorIndex = 0; cardByColorIndex < DeckData::AMOUNT_OF_NORMAL_CARDS_BY_COLOR; cardByColorIndex++)
	{
		for (int numberIndex = 0; numberIndex < DeckData::NUMBER_RANGE_IN_CARDS; numberIndex++)
		{
			std::shared_ptr<NumberCard> card = std::make_shared<NumberCard>(card, cardColor, std::to_string(numberIndex));
			_cards.push_back(card);
		}
	}
}

void DeckManager::CreateJumpCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_JUMP_CARDS_BY_COLOR; cardIndex++)
	{
		std::shared_ptr<JumpCard> card = std::make_shared<JumpCard>(card, cardColor, DeckData::PLUS_TWO_SYMBOL);
		_cards.push_back(card);
	}
}

void DeckManager::CreateReverseCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_REVERSE_CARDS_BY_COLOR; cardIndex++)
	{
		std::shared_ptr<ReverseCard> card = std::make_shared<ReverseCard>(card, cardColor, DeckData::REVERSE_SYMBOL);
		_cards.push_back(card);
	}
}
void DeckManager::CreatePlusTwoCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_PLUS_TWO_CARDS_BY_COLOR; cardIndex++)
	{
		std::shared_ptr<PlusTwoCard> card = std::make_shared<PlusTwoCard>(card, cardColor, DeckData::PLUS_TWO_SYMBOL);
		_cards.push_back(card);
	}
}


void DeckManager::ShuffleDeck()
{
}

void DeckManager::ResetDeck()
{
}

void DeckManager::GetBackPlayerCards()
{
}

std::shared_ptr<BaseCard> DeckManager::GetTopCard()
{
	//TODO fix me
	return _cards[0];
}

std::shared_ptr<BaseCard> DeckManager::BuyTopCardAndRemoveFromDeck()
{
	//TODO fix me
	return _cards[0];
}
