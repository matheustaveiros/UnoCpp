#include "ConsoleRenderEntity.h"
#include <iostream>

void ConsoleRenderEntity::Draw(std::string& lineText)
{
	std::cout << lineText << std::endl;
}