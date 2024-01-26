#include <algorithm>
#include <random>
#include "Cards/NumberCard.h"
#include "Cards/JumpCard.h"
#include "Cards/ReverseCard.h"
#include "Cards/PlusTwoCard.h"
#include "Cards/PlusFourCard.h"
#include "Cards/SwapHandsCard.h"
#include "Cards/ChooseColorCard.h"
#include "Cards/BuyFromDiscardPileCard.h"
#include "Core/TurnHandler.h"
#include "Console/ConsoleHelper.h"
#include "Utils/RandomHelper.h"
#include "Player/Player.h"
#include "DeckData.h"
#include "DeckManager.h"

void DeckManager::Initialize(std::shared_ptr<TurnHandler> turnHandler, std::shared_ptr<PlayersManager> playersManager)
{
	_turnHandler = turnHandler;
	_playersManager = playersManager;
}

void DeckManager::CreateDeck()
{
	using enum Enums::CardColor;
	std::vector<Enums::CardColor> colorList{ Red, Green, Blue, Yellow };

	for (int i = 0; i < static_cast<int>(colorList.size()); i++)
	{
		Enums::CardColor cardColor = colorList[i];
		CreateNumberCards(cardColor);
		CreateJumpCards(cardColor);
		CreateReverseCards(cardColor);
		CreatePlusTwoCards(cardColor);
		CreateSwapHandsCards(cardColor);
		CreateBuyFromDiscardPileCards(cardColor);
	}

	CreatePlusFourCards(Black);
	CreateChooseColorCards(Black);

	ConsoleHelper::PrintMessage("Cards Created\n", Enums::DisplayLevel::Developer);

	ShuffleDeck();
}

void DeckManager::CreateNumberCards(Enums::CardColor cardColor)
{
	for (int cardByColorIndex = 0; cardByColorIndex < DeckData::AMOUNT_OF_NORMAL_CARDS_BY_COLOR; cardByColorIndex++)
	{
		for (int numberIndex = 0; numberIndex <= DeckData::NUMBER_RANGE_IN_CARDS; numberIndex++)
		{
			auto card = std::make_shared<NumberCard>(_turnHandler, cardColor, std::to_string(numberIndex));
			_deck.push_back(card);
		}
	}
}

void DeckManager::CreateJumpCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_JUMP_CARDS_BY_COLOR; cardIndex++)
	{
		auto card = std::make_shared<JumpCard>(_turnHandler, cardColor, DeckData::JUMP_CARD_SYMBOL);
		_deck.push_back(card);
	}
}

void DeckManager::CreateReverseCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_REVERSE_CARDS_BY_COLOR; cardIndex++)
	{
		auto card = std::make_shared<ReverseCard>(_turnHandler, cardColor, DeckData::REVERSE_SYMBOL);
		_deck.push_back(card);
	}
}

void DeckManager::CreatePlusTwoCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_PLUS_TWO_CARDS_BY_COLOR; cardIndex++)
	{
		auto card = std::make_shared<PlusTwoCard>(_turnHandler, cardColor, DeckData::PLUS_TWO_SYMBOL);
		_deck.push_back(card);
	}
}

void DeckManager::CreateSwapHandsCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_SWAP_HANDS_CARDS_BY_COLOR; cardIndex++)
	{
		auto card = std::make_shared<SwapHandsCard>(_turnHandler, cardColor, DeckData::SWAP_CARD_SYMBOL);
		_deck.push_back(card);
	}
}

void DeckManager::CreateBuyFromDiscardPileCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_BUY_FROM_DISCARD_PILE_CARDS_BY_COLOR; cardIndex++)
	{
		auto card = std::make_shared<BuyFromDiscardPileCard>(_turnHandler, cardColor, DeckData::BUY_FROM_DISCARD_PILE_CARD_SYMBOL, 2);
		_deck.push_back(card);
	}
}

void DeckManager::CreatePlusFourCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_PLUS_FOUR_CARDS; cardIndex++)
	{
		auto card = std::make_shared<PlusFourCard>(_turnHandler, cardColor, DeckData::PLUS_FOUR_SYMBOL);
		_deck.push_back(card);
	}
}

void DeckManager::CreateChooseColorCards(Enums::CardColor cardColor)
{
	for (int cardIndex = 0; cardIndex < DeckData::AMOUNT_OF_CHOOSE_COLOR_CARDS; cardIndex++)
	{
		auto card = std::make_shared<ChooseColorCard>(_turnHandler, cardColor, DeckData::CHOOSE_COLOR_CARD_SYMBOL);
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
		std::ranges::copy(playerCards.begin(), playerCards.end(), std::back_inserter(_deck));

		players[i]->CleanPlayerHand();
	}
}

void DeckManager::ResetDiscardPile()
{
	std::ranges::copy(_discardPile.begin(), _discardPile.end(), std::back_inserter(_deck));
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

std::shared_ptr<BaseCard> DeckManager::BuyTopCardAndRemoveFromDiscardPile()
{
	if (_discardPile.size() <= 1)
	{
		ConsoleHelper::PrintMessage("Discard Pile is Empty, Adding One Card From Deck Into Stack\n");
		return BuyTopCardAndRemoveFromDeck();
	}

	std::shared_ptr<BaseCard> topCard = GetTopCardFromDiscardPile(); //Get last thrown card to ignore, will be the card used on this turn.

	int randomNumber = 0;
	do
	{
		randomNumber = RandomHelper::Range(0, static_cast<int>(_discardPile.size()) - 1);
	}
	while (_discardPile[randomNumber] == topCard);

	std::shared_ptr<BaseCard> selectedCard = _discardPile[randomNumber];
	_discardPile.erase(_discardPile.begin() + randomNumber);

	ConsoleHelper::PrintMessage("One Card Added From Discard Pile Into Stack\n");
	return selectedCard;
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

std::shared_ptr<BaseCard> DeckManager::GetFirstNumberCardOnDeckAndRemoveIt() //TODO: consider using weak pointer
{
	for (int i = 0; i < _deck.size(); i++)
	{
		if (std::shared_ptr<NumberCard> numberCard = std::dynamic_pointer_cast<NumberCard>(_deck[i]))
		{
			_deck.erase(_deck.begin() + i);
			return numberCard;
		}
	}

	return {}; //same as null_ptr
}