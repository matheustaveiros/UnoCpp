#pragma once
#include <string>
class DeckData
{
public:
	static const int NUMBER_RANGE_IN_CARDS = 9;
	static const int AMOUNT_OF_NORMAL_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_REVERSE_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_PLUS_TWO_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_JUMP_CARDS_BY_COLOR = 2;
	static const int AMOUNT_OF_INITIAL_CARDS = 7;
	static std::string PLUS_TWO_SYMBOL;
	static std::string REVERSE_SYMBOL;
	static std::string JUMP_CARD_SYMBOL;
};

