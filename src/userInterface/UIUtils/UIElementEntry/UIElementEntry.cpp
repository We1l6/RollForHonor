#include "UIElementEntry.h"

UIElementEntry::UIElementEntry(std::shared_ptr<UserInterface> elem, int zIdx)
	: element(std::move(elem)), zIndex(zIdx) 
{
	if (!element) 
		LOG_ERROR("UIElementEntry created with a null element");
}