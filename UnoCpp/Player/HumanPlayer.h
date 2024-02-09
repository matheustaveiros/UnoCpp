#pragma once
#include "Player.h"
class HumanPlayer : public Player
{

private:
	int _yellUnoActionValue = 0;
	int _buyCardActionValue = 0;

	void ShowExtraActions();
	void WaitForActionInput();
	void HandleMandatoryPlay();
	void ShowCompatibleOptions();
	void UseOption(int option);

public:
	HumanPlayer(TurnHandler* turnHandler, const std::string& name);
	void StartTurn() override;
	void AskToSelectAColor() override;
	void AskForHandToSwap() override;
};

