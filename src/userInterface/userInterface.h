/**
 * @file UserInterface.h
 * @brief Base class for all UI elements.
 *
 * Serves as a common interface and foundation for UI components.
 * Encapsulates text rendering, rectangular geometry, and skin styling.
 * Provides virtual Draw() and Update() methods for derived classes to override.
 * Manages visual and positional properties such as position, size, rotation, and corner radius.
 * Intended to be used as a superclass for interactive UI elements like buttons, sliders, etc.
 *
 * @note Inherit from UserInterface to create reusable and styled UI components.
 * Text and geometry are automatically aligned through internal helpers like updateTextPosition().
 *
 * @example
 * class MyButton : public UserInterface
 * {
 *     void Draw() override
 *     {
 *         m_skin.Draw(m_rect);
 *         m_text.Draw();
 *     }
 * };
 *
 * MyButton btn(...);
 * btn.setText("Click me");
 * btn.setPosition({100, 100});
 * btn.Draw();
 *
 * @author koliruslik
 * @date 14/06/2025
 */

#pragma once


#include <algorithm>
#include <cmath>
#include <string>

#include "../loggerManager/loggerManager.h"
#include "UIUtils/RectanglePro/RectanglePro.h"
#include "UIUtils/TextPro/TextPro.h"
#include "UIUtils/UISkin/UISkin.h"
#include "raylib.h"


/**
* Base class for all UI elements
* Accessible only through a UI element.
*/

class UserInterface {
protected:
  TextPro m_text;
  RectanglePro m_rect;
  UISkin m_skin;

  void updateTextPosition();
public:

	UserInterface(const RectanglePro& rect, const UISkin& skin);
	UserInterface(const RectanglePro& rect, const UISkin& skin, const TextPro& text);

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
	[[nodiscard]] Color getColor() const { return m_skin.getColor(); }

	//Setters
	void setSize(Vector2 size);
	void setPosition(Vector2 position);
	void setText(const std::string& text);
	
};
