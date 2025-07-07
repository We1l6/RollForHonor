#include "uiPanel.h"

UIPanel::UIPanel(const RectanglePro& rect, const UISkin& skin)
	: UserInterface(rect, skin), m_needsSort(true)
{
}

void UIPanel::DrawPanel()
{
	m_skin.Draw(m_rect);
}

void UIPanel::Draw() 
{
	if (m_needsSort)
	{
		std::stable_sort(m_elements.begin(), m_elements.end(),
			[]
			(const UIElementEntry& a, const UIElementEntry& b) 
			{ return a.zIndex < b.zIndex; });
		m_needsSort = false;
	}

	for (const auto& entry : m_elements)
	{
		if(entry.element && entry.element->isVisible())
			entry.element->Draw();
	}
}

void UIPanel::Update() 
{
	for (const auto& entry : m_elements) 
	{
		if (entry.element) 
		{
			entry.element->Update();
		}
	}
}

/**
 * @param element: Pointer to the UI element to be added
 * @param localPosition: Position relative to the panel's top-left corner
 */
void UIPanel::AddElement(std::shared_ptr<UserInterface> element, Vector2 localPosition, int zIndex)
{
	if (!element)
	{
		LoggerManager::LOG_ERROR("Attempted to add a null element to UIPanel");
	}

	Vector2 panelTopLeft = m_rect.getOrigin();
	Vector2 absolutePosition = Vector2Add(panelTopLeft, localPosition);
	element->setPosition(absolutePosition);

	m_elements.emplace_back(std::move(element), zIndex);
	m_needsSort = true;
}

void UIPanel::ChangeElementZIndex(std::shared_ptr<UserInterface> element, int newZIndex)
{
	for (auto& entry : m_elements)
	{
		if (entry.element == element)
		{
			entry.zIndex = newZIndex;
			m_needsSort = true;
			return;
		}
	}
}

int UIPanel::GetHighestZIndex() const
{
	int maxZ = 0;
	for (const auto& e : m_elements)
		if (e.zIndex > maxZ)
			maxZ = e.zIndex;
	return maxZ;
}

int UIPanel::GetLowestZIndex() const
{
	int minZ = 0;
	for (const auto& e : m_elements)
		if (e.zIndex < minZ)
			minZ = e.zIndex;
	return minZ;
}

void UIPanel::BringToFront(std::shared_ptr<UserInterface> element)
{
	ChangeElementZIndex(element, GetHighestZIndex() + 1);
}

void UIPanel::SendToBack(std::shared_ptr<UserInterface> element)
{
	ChangeElementZIndex(element, GetLowestZIndex() - 1);
}

Vector2 UIPanel::getLocalCenter()
{
	Vector2 size = m_rect.getSize();
	return Vector2{
		size.x / 2.0f,
		size.y / 2.0f
	};

}