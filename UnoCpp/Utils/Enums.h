#pragma once
#include <vector>
#include <string>
#include <iostream>

class Enums
{
public:
	enum class CardColor
	{
		Empty,
		Blue,
		Green,
		Red,
		Yellow,
		Black
	};

	enum class DisplayLevel
	{
		Developer,
		Player
	};

	static std::string_view GetColorDisplayName(const CardColor color);
};