#include "userInterface.h"

UserInterface::UserInterface(const RectanglePro& rect, const UISkin& skin)
    : UserInterface(rect, skin, TextPro(std::string(""))) { }

UserInterface::UserInterface(const RectanglePro& rect, const UISkin& skin, const TextPro& text)
	: m_rect(rect), m_text(text), m_skin(skin), m_visible(true), m_zIndex(0)
{
	updateTextPosition();
	m_text.setRotation(m_rect.getRotation());
}

void UserInterface::Update() { this->Draw(); }

void UserInterface::Draw() {
    m_skin.Draw(m_rect);
	m_text.Draw();
}

void UserInterface::setSize(Vector2 size)
{
	m_rect.setSize(size);
	updateTextPosition();
}

void UserInterface::setPosition(Vector2 pos)
{
	m_rect.setPosition(pos);
	updateTextPosition();
}

void UserInterface::updateTextPosition() {
	Vector2 center = m_rect.getPosition();
	m_text.setPosition(center);
}

void UserInterface::setText(const std::string& text)
{
	m_text.setText(text);
	updateTextPosition();
}
