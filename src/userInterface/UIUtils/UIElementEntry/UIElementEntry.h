#pragma once

#include <memory>
#include "../../userInterface.h"

struct UIElementEntry
{
	std::shared_ptr<UserInterface> element;
	int zIndex;

	UIElementEntry(std::shared_ptr<UserInterface> elem, int zIdx);
};