#pragma once

#include "Enums.h"
#include <string>

class BaseCard
{
private:
	Enums::CardColor color;
	std::string symbol;

public:
	Enums::CardColor GetColor() const;
	std::string GetSymbol();
};

