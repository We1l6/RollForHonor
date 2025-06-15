#include "button.h"

Button::Button(const RectanglePro& rect, const TextPro& text)
	: UserInterface(rect, text)
{
	m_baseSize = m_rect.getSize();
	m_onHold = [this]() { defaultOnHold(); };
	m_onClickFinished = [this]() { defaultOnClickFinished(); };
}

Button::Button(const RectanglePro& rect, const TextPro& text,
	ButtonCallback onHold,
	ButtonCallback onClickFinished) 
	: UserInterface(rect, text), m_onHold(onHold), m_onClickFinished(onClickFinished)
{
	m_baseSize = m_rect.getSize();
}
void Button::Update()
{
	Draw();
	Vector2 mousePosition = GetMousePosition();

	m_hovered = CheckCollisionPointRec(mousePosition, m_rect);

	if (m_hovered)
	{
		m_rect.setColor(HOVER_COLOR);

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) 
			safeInvoke(m_onHold);
		else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
			safeInvoke(m_onClickFinished);

	}
	else
		resetToDefault();
}

void Button::defaultOnHold()
{
	this->setSize({ m_baseSize.x + SIZE_OFFSET_ON_HOLD, m_baseSize.y + SIZE_OFFSET_ON_HOLD });
	this->setColor(HOLD_COLOR);
}
void Button::defaultOnClickFinished()
{
	this->setSize(m_baseSize);
	this->setColor(DEFAULT_COLOR);
}

void Button::resetToDefault()
{
	this->setSize(m_baseSize);
	this->setColor(DEFAULT_COLOR);
	m_hovered = false;
}

void Button::safeInvoke(const ButtonCallback& callback)
{
	try {
		if (callback) callback();
	}
	catch (const std::exception& e) {
		LOG_ERROR("Button callback threw an exception: {}", e.what());
	}
	catch (...) {
		LOG_ERROR("Unknown exception in button callback");
	}
}
