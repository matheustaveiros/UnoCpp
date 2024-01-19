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
#include "RandomHelper.h"
#include "Player.h"

DeckManager::DeckManager(std::shared_ptr<PlayersManager> playersManager) : _playersManager { playersManager }
{
	
}

void DeckManager::Initialize(std::shared_ptr<TurnHandler> turnHandler)
{
	_turnHandler = turnHandler;
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
			std::shared_ptr<NumberCard> card = std::make_shared<NumberCard>(_turnHandler, card, cardColor, std::to_string(numberIndex));
			_deck.push_back(card);
		}
	}
}

void DeckManager::CreateJumpCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_JUMP_CARDS_BY_COLOR; cardIndex++)
	{
		std::shared_ptr<JumpCard> card = std::make_shared<JumpCard>(_turnHandler, card, cardColor, DeckData::PLUS_TWO_SYMBOL);
		_deck.push_back(card);
	}
}

void DeckManager::CreateReverseCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_REVERSE_CARDS_BY_COLOR; cardIndex++)
	{
		std::shared_ptr<ReverseCard> card = std::make_shared<ReverseCard>(_turnHandler, card, cardColor, DeckData::REVERSE_SYMBOL);
		_deck.push_back(card);
	}
}
void DeckManager::CreatePlusTwoCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_PLUS_TWO_CARDS_BY_COLOR; cardIndex++)
	{
		std::shared_ptr<PlusTwoCard> card = std::make_shared<PlusTwoCard>(_turnHandler, card, cardColor, DeckData::PLUS_TWO_SYMBOL);
		_deck.push_back(card);
	}
}


void DeckManager::ShuffleDeck()
{
	std::ranges::shuffle(_deck, RandomHelper::Generator);

	ConsoleHelper::PrintMessage("Cards Shuffled\n", Enums::DisplayLevel::Developer);
}

void DeckManager::ResetAllCards()
{
	GetBackPlayerCards();
	ResetDiscardPile();
}

void DeckManager::GetBackPlayerCards()
{
	std::vector<std::shared_ptr<Player>> players = _playersManager->GetPlayers();
	for (int i = 0; i < players.size(); i++)
	{
		std::vector<std::shared_ptr<BaseCard>> playerCards = players[i]->GetCards();
		std::copy(playerCards.begin(), playerCards.end(), std::back_inserter(_deck));

		players[i]->CleanPlayerHand();
	}
}

void DeckManager::ResetDiscardPile()
{
	std::copy(_discardPile.begin(), _discardPile.end(), std::back_inserter(_deck));
	_discardPile.clear();
}

std::shared_ptr<BaseCard> DeckManager::GetTopCardFromDeck()
{
	if (_deck.empty())
	{
		KeepLastCardAndResetDiscardPile();
	}

	return _deck.back();
}

std::shared_ptr<BaseCard> DeckManager::BuyTopCardAndRemoveFromDeck()
{
	if (_deck.empty())
	{
		KeepLastCardAndResetDiscardPile();
	}

	std::shared_ptr<BaseCard> card = _deck.back();
	_deck.pop_back();
	return card;
}

void DeckManager::AddCardToDiscardPile(std::shared_ptr<BaseCard> card)
{
	_discardPile.push_back(card);
}

std::shared_ptr<BaseCard> DeckManager::GetTopCardFromDiscardPile()
{
	return _discardPile.back();
}

void DeckManager::KeepLastCardAndResetDiscardPile()
{
	std::shared_ptr<BaseCard> discardTopCard = _discardPile.back();
	_discardPile.pop_back();

	std::ranges::copy(_discardPile.begin(), _discardPile.end(), std::back_inserter(_deck));
	_discardPile.push_back(discardTopCard);
}

std::shared_ptr<BaseCard> DeckManager::GetFirstNumberCardOnDeckAndRemoveIt()
{
	for (int i = 0; i < _deck.size(); i++)
	{
		if (std::shared_ptr<NumberCard> numberCard = std::dynamic_pointer_cast<NumberCard>(_deck[i]))
		{
			_deck.erase(_deck.begin() + i);
			return numberCard;
		}
	}

	return nullptr;
}