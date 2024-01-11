#pragma once

#include "Enums.h"
#include <string>
#include "TurnHandler.h"
class BaseCard
{
private:
	Enums::CardColor _color;
	std::string _symbol;

	TurnHandler& _turnHandler;

public:
	Enums::CardColor GetColor() const;
	std::string GetSymbol() const;
};

