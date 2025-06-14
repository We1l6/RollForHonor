#pragma once

#include <algorithm>
#include <cmath>
#include <string>

#include "UIUtils.h"
#include "raylib.h"

class UserInterface {
protected:
  inline static const int DEFAULT_FONT_SIZE = 20;
  TextPro m_text;
  RectanglePro m_rect;

  UserInterface(RectanglePro &rect);
  UserInterface(RectanglePro &rect, TextPro &text);

public:
  virtual ~UserInterface() = default;
  // Getters
  [[nodiscard]] RectanglePro GetBounds() const { return m_rect; }
  [[nodiscard]] float GetWidth() const { return m_rect.width; }
  [[nodiscard]] float GetHeight() const { return m_rect.height; }
  [[nodiscard]] float GetX() const { return m_rect.x; }
  [[nodiscard]] float GetY() const { return m_rect.y; }
  // Setters
  void SetBounds(RectanglePro bounds) { m_rect = bounds; }
  void SetPosition(float &x, float &y) {
    m_rect.x = x;
    m_rect.y = y;
  }

  // bool isHovered() const { return m_isHovered; }

  virtual void Draw();
  virtual void Update();
  virtual void HandleInput();

private:
  /*bool m_isHovered = false;
  bool m_isPressed = false;*/
};
