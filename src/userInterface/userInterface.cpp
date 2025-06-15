#include "userInterface.h"

UserInterface::UserInterface(const RectanglePro& rect)
    : UserInterface(rect, TextPro(std::string(""))) { }

UserInterface::UserInterface(const RectanglePro& rect, const TextPro& text)
    : m_rect(rect), m_text(text)
{
  m_text.setPosition({
      .x = m_rect.x + (m_rect.width / 2.0f),
      .y = m_rect.y + (m_rect.height / 2.0f)
  });

  m_text.setRotation(m_rect.getRotation());
}

void UserInterface::setSize(Vector2 size)
{
	m_rect.setSize(size);
	m_text.setPosition({
		.x = m_rect.x + (m_rect.width / 2.0f),
		.y = m_rect.y + (m_rect.height / 2.0f)
		});
}

void UserInterface::setPosition(Vector2 pos)
{
	m_rect.setPosition(pos);
	m_text.setPosition({
		.x = m_rect.x + (m_rect.width / 2.0f),
		.y = m_rect.y + (m_rect.height / 2.0f)
		});
}

void UserInterface::Draw() {
    m_rect.Draw();
	m_text.Draw();
}

void UserInterface::Update() { this->Draw(); }
