#pragma once

#include <algorithm>
#include <cmath>
#include <string>

#include "../loggerManager/loggerManager.h"
#include "UIUtils/RectanglePro/RectanglePro.h"
#include "UIUtils/TextPro/TextPro.h"
#include "raylib.h"


/**
 * @brief Represents a base class for user interface elements.
 * This class provides basic functionality for drawing and updating UI elements.
 */
class UserInterface {
protected:
  TextPro m_text;
  RectanglePro m_rect;
  
public:

	UserInterface(const RectanglePro& rect);
	UserInterface(const RectanglePro& rect, const TextPro& text);
	// Default constructor
	UserInterface() = default; 
	virtual ~UserInterface() = default;

	virtual void Draw();
	virtual void Update();

	void setSize(Vector2 size);
	void setPosition(Vector2 position);

	//Getters
	[[nodiscard]] RectanglePro GetRectanglePro() const { return m_rect; }
	[[nodiscard]] TextPro GetTextPro() const { return m_text; }
};
