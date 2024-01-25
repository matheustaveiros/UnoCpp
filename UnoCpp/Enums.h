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

//template <>
//struct std::formatter<Enums::CardColor> : std::formatter<std::string>
//{
//	template <typename FormatContext>
//	auto format(Enums::CardColor color, FormatContext& context)
//	{
//		const std::array<char*> colorNames = { "Empty", "Blue", "Green", "Red", "Yellow", "Black" };
//		return std::formatter<std::string>::format(colorNames[static_cast<int>(color)], context);
//	}
//};

//template <typename EnumType>
//std::string to_string(const EnumType& enumValue)
//{
//	static_assert(std::is_enum<EnumType>::value, "EnumType must be an enum type");
//
//	const std::array<char*> enumStrings = { "Empty", "Blue", "Green", "Red", "Yellow", "Black" };
//
//	int index = static_cast<int>(enumValue);
//
//	// Add bounds checking to prevent out-of-range access
//	if (index >= 0 && index < sizeof(enumStrings) / sizeof(enumStrings[0])) {
//		return enumStrings[index];
//	}
//	else {
//		return "Unknown";
//	}
//}