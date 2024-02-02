#pragma once
#include <string>
class DeckData
{
public:
	static const int NUMBER_RANGE_IN_CARDS = 1;
	static const int AMOUNT_OF_NORMAL_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_REVERSE_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_PLUS_TWO_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_BUY_FROM_DISCARD_PILE_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_JUMP_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_SWAP_HANDS_CARDS_BY_COLOR = 10;
	static const int AMOUNT_OF_PLUS_FOUR_CARDS = 4;
	static const int AMOUNT_OF_CHOOSE_COLOR_CARDS = 4;
	static const int AMOUNT_OF_INITIAL_CARDS = 7;
	static const int PENALTY_FOR_NOT_YELL_UNO = 2;
	static const std::string PLUS_TWO_SYMBOL;
	static const std::string PLUS_FOUR_SYMBOL;
	static const std::string REVERSE_SYMBOL;
	static const std::string JUMP_CARD_SYMBOL;
	static const std::string SWAP_CARD_SYMBOL;
	static const std::string CHOOSE_COLOR_CARD_SYMBOL;
	static const std::string BUY_FROM_DISCARD_PILE_CARD_SYMBOL;
};

