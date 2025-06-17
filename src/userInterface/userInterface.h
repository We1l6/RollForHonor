/**
 * @file UserInterface.h
 * @brief Base class for all UI elements
 * @details
 * Serves as a common interface and foundation for UI components.
 * Encapsulates text, rectangular geometry, and skin styling.
 * Provides basic drawing and updating functionality, intended to be overridden by derived classes.
 * Manages position, size, rotation, and appearance properties.
 * Accessible only via UI elements derived from this base.
 *
 * @author koliruslik
 * @date 17/06/2025
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
