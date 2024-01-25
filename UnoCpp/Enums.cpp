#include "Enums.h"

std::string_view Enums::GetColorDisplayName(const CardColor color)
{
    switch (color)
    {
    using enum Enums::CardColor;
    case Empty:
        return "Empty";
    case Blue:
        return "Blue";
    case Yellow:
        return "Yellow";
    case Red:
        return "Red";
    case Green:
        return "Green";
    case Black:
        return "Black";
    default:    
        return "Empty";
    }

    return "Empty";
}