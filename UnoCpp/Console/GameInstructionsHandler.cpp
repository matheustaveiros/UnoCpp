#include <string>
#include <format>
#include "ConsoleHelper.h"
#include "GameInstructionsHandler.h"

void GameInstructionsHandler::DrawInstructions()
{
	std::string message = "Cards Glossary: \n";
	message += "+2 -> Make the next player purchase 2 cards from Deck\n";
	message += "D+2 -> Make the next player purchase 2 cards from Discard Pile\n";
	message += "Rev -> Change the game Direction\n";
	message += "Blk -> Jump the next player\n";
	message += "Swp -> Swap player hands with any selected player\n";
	message += "Wld -> Change Color card, you can throw it ignoring the current card color\n";
	message += "+4 -> Make the next player purchase 4 cards from Deck, and you can throw it ignoring the current card color\n";

	message += "\nSpecial Behavior:\n";
	message += "You can throw +2, D+2 and +4 to defend yourself from these card abilities, but note, you can only use the specific type to defend\n";
	message += "For example, if the previous player throw +2, and have to play a +2 card to defend, the +2 or D+2 is not allowed\n";
	message += "Black Cards, all the Black cards can be used ignoring the Color and they allow you to Choose for a color after the usage\n";
	
	message += "\nYell Uno:\n";
	message += "\nThe player Must Yell Uno before throwing a card and only 1 card remaining in hand\n";
	message += "\nThe penalty for not yelling Uno will be applied and the player will get 2 cards from the Deck\n";

	message += "\nWin Condition:\n";
	message += "The first player to use all his cards will win the game\n";

	ConsoleHelper::PrintMessage(message);
	ConsoleHelper::WaitForAnyKey("\nPress Any Key to Skip\n", Enums::CardColor::Yellow);
	ConsoleHelper::Clear();
}
