#pragma once

#include <algorithm>
#include <cmath>
#include <string>

#include "UIUtils/RectanglePro/RectanglePro.h"
#include "UIUtils/TextPro/TextPro.h"
#include "raylib.h"

class UserInterface {
protected:
  TextPro m_text;
  RectanglePro m_rect;

  UserInterface(const RectanglePro& rect);
  UserInterface(const RectanglePro& rect, const TextPro& text);

public:
	// Default constructor
	UserInterface() = default; 
	virtual ~UserInterface() = default;
	//Getters
	[[nodiscard]] RectanglePro GetRectanglePro() const { return m_rect; }

	// bool isHovered() const { return m_isHovered; }

	virtual void Draw();
	virtual void Update();
	virtual void HandleInput();

private:
  /*bool m_isHovered = false;
  bool m_isPressed = false;*/
};
