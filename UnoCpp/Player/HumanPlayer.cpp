#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(TurnHandler* turnHandler, const std::string_view name) : Player(turnHandler, name)
{

}

void HumanPlayer::StartTurn()
{
    _yellUnoActionValue = -1;
    _buyCardActionValue = -2;
    DrawTopCardFromDiscardPile();
    if (_turnHandler->HasCardsStacked())
    {
        HandleMandatoryPlay();
    }
    else
    {
        DrawCards();
        ShowExtraActions();
        WaitForActionInput();
    }
}

void HumanPlayer::ShowExtraActions()
{
    int startOffset = static_cast<int>(GetCards().size());
    _buyCardActionValue = startOffset;
    _yellUnoActionValue = startOffset + 1;

    ConsoleHelper::PrintMessage("Type Any Card Id to Use Or\n");
    ConsoleHelper::PrintMessage(std::format("Type {} to Buy One Card\n", _buyCardActionValue));
    ConsoleHelper::PrintMessage(std::format("Type {} to Yell Uno!\n", _yellUnoActionValue));
}

void HumanPlayer::WaitForActionInput()
{
    int selectedAction = ConsoleHelper::GetInput<int>("Insert the number of the action to Play: \n", Enums::CardColor::Yellow);
    UseOption(selectedAction);
}

void HumanPlayer::HandleMandatoryPlay()
{
    ConsoleHelper::Clear();
    DrawTopCardFromDiscardPile();
    DrawCards();

    const BaseCard* topCard = _turnHandler->GetTopCardFromDiscardPile();
    ConsoleHelper::PrintMessage("Mandatory Use of Special Card Type: " + topCard->GetSymbol() + "\n", Enums::CardColor::Yellow);

    ShowCompatibleOptions();
}

void HumanPlayer::ShowCompatibleOptions()
{
    std::vector<int> validCards;
    std::string displayText = "Select the Following Options to Play: ";
    for (int i = 0; i < GetCards().size(); i++)
    {
        BaseCard* handCard = GetCard(i);
        if (CardIsSymbolOnlyCompatible(handCard))
        {
            displayText += std::format("({}) ", i);
            validCards.emplace_back(i);
        }
    }

    if (validCards.empty())
    {
        ConsoleHelper::PrintMessage("No Compatible Card to Throw\n", Enums::CardColor::Red);
        _turnHandler->ApplyStackCardsToPlayer();
        _turnHandler->SkipToNextPlayer();
    }
    else
    {
        displayText += "\n";

        int selectedAction = ConsoleHelper::GetInput<int>(displayText);
        for (const int& cardNumber : validCards)
        {
            if (selectedAction == cardNumber)
            {
                UseOption(selectedAction);
                break;
            }
        }
    }
}

void HumanPlayer::UseOption(int option)
{
    ConsoleHelper::Clear();

    if (option == _yellUnoActionValue)
    {
        HandleYellUnoOption();
    }
    else if (option == _buyCardActionValue)
    {
        HandleBuyCardOption();
    }
    else
    {
        HandleUseCardOption(option);
    }
}

void HumanPlayer::AskToSelectAColor()
{
    using enum Enums::CardColor;

    ConsoleHelper::PrintMessage("Your Cards:\n");
    DrawCards();

    int selectedColor = ConsoleHelper::GetInput<int>(std::format("Please Select a Color By Number For The Next Play: Blue ({}), Green ({}), Red ({}), Yellow ({})\n",
        static_cast<int>(Blue), static_cast<int>(Green), static_cast<int>(Red), static_cast<int>(Yellow)));
    if (selectedColor <= 0 || selectedColor > 4)
    {
        ConsoleHelper::PrintMessage(std::format("Invalid Input, Please Select a Valid Number ({}, {}, {}, {})\n",
            static_cast<int>(Blue), static_cast<int>(Green), static_cast<int>(Red), static_cast<int>(Yellow)), Enums::CardColor::Red);
        AskToSelectAColor();
    }
    else
    {
        ConsoleHelper::Clear();
        _turnHandler->SetSelectedColor(selectedColor);
    }
}

void HumanPlayer::AskForHandToSwap()
{
    std::vector<int> validIds;
    std::string idsText;
    for (int i = 0; i < _turnHandler->GetPlayerAmount(); i++)
    {
        if (i == _turnHandler->GetCurrentPlayerIndex())
            continue;

        validIds.emplace_back(i);
        idsText += std::format("->({}) Player: {} | Cards in Hand: {}\n", std::to_string(i), _turnHandler->GetPlayerNameByIndex(i), _turnHandler->GetPlayerCardAmountById(i));
    }

    int selectedPlayer = ConsoleHelper::GetInput<int>(std::format("Type the Player ID To Swap Hands: \n{}", idsText));
    if (selectedPlayer != _turnHandler->GetCurrentPlayerIndex() && selectedPlayer >= 0 && selectedPlayer < _turnHandler->GetPlayerAmount())
    {
        ConsoleHelper::Clear();
        _turnHandler->SwapHand(selectedPlayer);
    }
    else
    {
        ConsoleHelper::PrintMessage("Invalid Input, Try Inserting a Valid Value\n", Enums::CardColor::Red);
        Sleep(1000);
        ConsoleHelper::Clear();
        AskForHandToSwap();
    }
}
