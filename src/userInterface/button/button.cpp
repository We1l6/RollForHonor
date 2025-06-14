#include "button.h"

Button::Button(const RectanglePro& rect, const TextPro& text)
	: Button(rect, text, 
		[this]() {m_rect.setColor(CLICK_COLOR); },
		[this]() {m_rect.setColor(DEFAULT_COLOR); }) {}

Button::Button(const RectanglePro& rect, const TextPro& text,
	ButtonCallback onClick,
	ButtonCallback onRelease) 
	: UserInterface(rect, text), m_onClick(onClick), m_onRelease(onRelease)
{
}
void Button::Update()
{
	Draw();
	mousePosition = GetMousePosition();
	m_hovered = CheckCollisionPointRec(mousePosition, m_rect);

	if (m_hovered) {
		m_rect.setColor(HOVER_COLOR);

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			if (m_onClick) {
				m_onClick();
			}
		}
		else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			if (m_onRelease) {
				m_onRelease();
			}
		}
	}
	else
	{
		m_rect.setColor(DEFAULT_COLOR);
	}
}