#pragma once
#include<string>
class RenderEntity
{
	virtual void Draw(std::string& lineText) = 0;
	//virtual ~RenderEntity() = default;
};

