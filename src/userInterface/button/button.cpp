#include "button.h"

Button::Button()
	: Button(RectanglePro(), UISkin(), TextPro())
{
}

Button::Button(const RectanglePro& rect, const UISkin& skin, const TextPro& text)
	: UserInterface(rect, skin, text)
{
	m_baseSize = m_rect.getSize();
	m_baseColor = m_skin.getColor();
	m_hasTexture = false;

	m_onHold = [this]() { defaultOnHold(); };
	m_onClickFinished = [this]() { defaultOnClickFinished(); };
}

Button::Button(const RectanglePro& rect, const UISkin& skin, const TextPro& text,
	ButtonCallback onHold,
	ButtonCallback onClickFinished) 
	: UserInterface(rect, skin, text), m_onHold(onHold), m_onClickFinished(onClickFinished)
{
	m_baseSize = m_rect.getSize();
	m_baseColor = m_skin.getColor();
	m_hasTexture = false;
}

Button::Button(const RectanglePro& rect, const UISkin& skin, const TextPro& text, ButtonCallback onHold,
	ButtonCallback onClickFinished, Texture2D texture)
	: UserInterface(rect, skin, text), m_onHold(onHold), m_onClickFinished(onClickFinished),
	m_texture(texture)
{
	m_baseSize = m_rect.getSize();
	m_baseColor = m_skin.getColor();
	m_hasTexture = true;
}

void Button::Draw()
{
	m_skin.Draw(m_rect);
	m_text.Draw();
}

void Button::Update()
{
	Vector2 mousePosition = GetMousePosition();

	if (m_isDragging) {
		safeInvoke(m_onHold);

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			safeInvoke(m_onClickFinished);
			m_isDragging = false;
		}
	}
	else {
		m_hovered = CheckCollisionPointRec(mousePosition, m_rect);

		if (m_hovered) {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				m_isDragging = true;
				safeInvoke(m_onHold);
			}
		}
		else {
			resetToDefault();
		}
	}
}

void Button::defaultOnHold()
{
	this->setSize({ m_baseSize.x + SIZE_OFFSET_ON_HOLD, m_baseSize.y + SIZE_OFFSET_ON_HOLD });
	m_skin.setColor(HOLD_COLOR);
}
void Button::defaultOnClickFinished()
{
	this->setSize(m_baseSize);
	m_skin.setColor(m_baseColor);
}

void Button::resetToDefault()
{
	this->setSize(m_baseSize);
	m_skin.setColor(m_baseColor);
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
}
