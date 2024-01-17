#include "DeckManager.h"
#include "DeckData.h"
#include "NumberCard.h"
#include "JumpCard.h"
#include "ReverseCard.h"
#include "PlusTwoCard.h"
#include <algorithm>
#include <random>
#include "TurnHandler.h"
#include "ConsoleHelper.h"

DeckManager::DeckManager(std::shared_ptr<PlayersManager> playersManager) : _playersManager { playersManager }
{
	
}

void DeckManager::CreateDeck()
{
	std::vector<Enums::CardColor> colorList{ Enums::CardColor::Blue, Enums::CardColor::Green, Enums::CardColor::Red, Enums::CardColor::Yellow };

	for (int i = 0; i < colorList.size(); i++)
	{
		Enums::CardColor cardColor = colorList[i];
		CreateNumberCards(cardColor);
		CreateJumpCards(cardColor);
		CreateReverseCards(cardColor);
		CreatePlusTwoCards(cardColor);
	}

	ConsoleHelper::PrintMessage("Cards Created\n", Enums::DisplayLevel::Developer);

	ShuffleDeck();
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
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(_cards), std::end(_cards), rng);

	ConsoleHelper::PrintMessage("Cards Shuffled\n", Enums::DisplayLevel::Developer);
}

void DeckManager::ResetDeck()
{
}

void DeckManager::GetBackPlayerCards()
{
	/*std::vector<std::shared_ptr<Player>> players = _playersManager->GetPlayers();
	for (int i = 0; i < players.size(); i++)
	{
		std::vector<std::shared_ptr<BaseCard>> playerCards = players[i]->GetCards();
		for (int j = 0; j < playerCards.size(); j++)
		{
			_cards.push_back(playerCards[j]);
		}

		players[i]->CleanPlayerHand();
	}*/

}

/// <summary>
/// Top card will be always first
/// </summary>
/// <returns></returns>
std::shared_ptr<BaseCard> DeckManager::GetTopCardFromDeck()
{
	if (_cards.empty())
	{
		return nullptr;
	}

	return _cards[0];
}

std::shared_ptr<BaseCard> DeckManager::BuyTopCardAndRemoveFromDeck()
{
	if (_cards.empty())
	{
		return nullptr;
	}

	std::shared_ptr<BaseCard> card = _cards[0];
	_cards.erase(_cards.begin());
	return card;
}

void DeckManager::AddCardToDiscardPile(std::shared_ptr<BaseCard> card)
{
	_discardPile.push_back(card);
}

std::shared_ptr<BaseCard> DeckManager::GetTopCardFromDiscardPile()
{
	return _discardPile[_discardPile.size() - 1];
}