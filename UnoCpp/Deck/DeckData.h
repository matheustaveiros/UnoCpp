#pragma once
#include <string>
class DeckData
{
public:
	static const int NUMBER_RANGE_IN_CARDS = 9;
	static const int AMOUNT_OF_NORMAL_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_REVERSE_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_PLUS_TWO_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_BUY_FROM_DISCARD_PILE_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_JUMP_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_SWAP_HANDS_CARDS_BY_COLOR = 1;
	static const int AMOUNT_OF_PLUS_FOUR_CARDS = 4;
	static const int AMOUNT_OF_CHOOSE_COLOR_CARDS = 4;
	static const int AMOUNT_OF_INITIAL_CARDS = 7;
	static const int PENALTY_FOR_NOT_YELL_UNO = 2;
	static std::string PLUS_TWO_SYMBOL;
	static std::string PLUS_FOUR_SYMBOL;
	static std::string REVERSE_SYMBOL;
	static std::string JUMP_CARD_SYMBOL;
	static std::string SWAP_CARD_SYMBOL;
	static std::string CHOOSE_COLOR_CARD_SYMBOL;
	static std::string BUY_FROM_DISCARD_PILE_CARD_SYMBOL;
};

