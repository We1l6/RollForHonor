#pragma once

#include <algorithm>
#include <cmath>
#include <string>

//#include "../loggerManager/loggerManager.h"
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
  void updateTextPosition();
public:

	UserInterface(const RectanglePro& rect);
	UserInterface(const RectanglePro& rect, const TextPro& text);
	// Default constructor
	UserInterface() = default; 
	virtual ~UserInterface() = default;

	virtual void Draw();
	virtual void Update();


	//Getters
	[[nodiscard]] RectanglePro getRectanglePro() const { return m_rect; }
	[[nodiscard]] TextPro getTextPro() const { return m_text; }
	[[nodiscard]] Vector2 getPosition() const { return m_rect.getPosition(); }
	[[nodiscard]] Vector2 getSize() const { return m_rect.getSize(); }
	[[nodiscard]] float getRotation() const { return m_rect.getRotation(); }
	[[nodiscard]] float getCornerRadius() const { return m_rect.getCornerRadius(); }
	[[nodiscard]] Color getColor() const { return m_rect.getColor(); }

	//Setters
	void setSize(Vector2 size);
	void setPosition(Vector2 position);
	void setText(const std::string& text);
	
};
