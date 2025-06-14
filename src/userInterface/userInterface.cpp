#include "userInterface.h"

UserInterface::UserInterface(RectanglePro &rect) : m_rect(rect), m_text("") {
  m_text.position = {.x = m_rect.x + (m_rect.width / 2.0f),
                     .y = m_rect.y + (m_rect.height / 2.0f)};
  m_text.rotation = m_rect.rotation;
  m_text.CenterOrigin();
}

UserInterface::UserInterface(RectanglePro &rect, TextPro &text)
    : m_rect(rect), m_text(text) {
  m_text.position = {.x = m_rect.x + (m_rect.width / 2.0f),
                     .y = m_rect.y + (m_rect.height / 2.0f)};
  m_text.rotation = m_rect.rotation;

  m_text.CenterOrigin();
}

void UserInterface::Draw() {
  // Font font = GetFontDefault();
  UIUtils::DrawRectangleProRounded(m_rect);
  UIUtils::DrawTextPro(m_text);
}

void UserInterface::Update() { this->Draw(); }

void UserInterface::HandleInput() {
  // Input handling can be implemented in derived classes
}
