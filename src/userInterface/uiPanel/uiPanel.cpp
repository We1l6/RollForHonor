#include "uiPanel.h"

UIPanel::UIPanel(const RectanglePro& rect, const UISkin& skin)
	: UserInterface(rect, skin), m_visible(true)
{
}

void UIPanel::Draw() 
{
	if(m_visible)m_skin.Draw(m_rect);
	for (const auto& element : m_elements) 
	{
		if (element) 
		{
			element->Draw();
		}
	}
}

void UIPanel::Update() 
{
	for (const auto& element : m_elements) 
	{
		if (element) 
		{
			element->Update();
		}
	}
}

/**
 * @param element: Pointer to the UI element to be added
 * @param localPosition: Position relative to the panel's top-left corner
 */
void UIPanel::AddElement(std::shared_ptr<UserInterface> element, Vector2 localPosition)
{
	if (element)
	{
		Vector2 panelTopLeft = m_rect.getOrigin();
		Vector2 absolutePosition = Vector2Add(panelTopLeft, localPosition);
		element->setPosition(absolutePosition);
		m_elements.push_back(element);
	}
	else
	{
		LoggerManager::LOG_ERROR("Attempted to add a null element to UIPanel");
	}
}

Vector2 UIPanel::getLocalCenter()
{
	Vector2 size = m_rect.getSize();
	return Vector2{
		size.x / 2.0f,
		size.y / 2.0f
	};

}