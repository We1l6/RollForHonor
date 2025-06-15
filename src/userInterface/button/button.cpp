#include "button.h"

Button::Button(const RectanglePro& rect, const TextPro& text)
	: Button(rect, text, 
		[this]() {m_rect.setColor(HOLD_COLOR); },
		[this]() {m_rect.setColor(DEFAULT_COLOR); }) {}

Button::Button(const RectanglePro& rect, const TextPro& text,
	ButtonCallback onHold,
	ButtonCallback onClickFinished) 
	: UserInterface(rect, text), m_onHold(onHold), m_onClickFinished(onClickFinished)
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
			if (m_onHold) {
				m_onHold();
			}
		}
		else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			if (m_onClickFinished) {
				m_onClickFinished();
			}
		}
	}
	else
	{
		m_rect.setColor(DEFAULT_COLOR);
	}
}