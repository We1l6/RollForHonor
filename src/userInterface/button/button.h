#pragma once

/**
 * @file Button.h
 * @brief Button UI element class
 * @details
 * Implements a clickable button with hover and drag states.
 * Supports setting callbacks for OnHold and OnClickFinished events.
 * Optionally displays a texture.
 * Update() must be called each frame to handle input and state changes.
 * Draw() renders the button on screen.
 *
 * @author koliruslik
 * @date 14/06/2025
 */

#include <functional>

#include "../userInterface.h"
#include "../../loggerManager/loggerManager.h"

using ButtonCallback = std::function<void()>;

/**
 * @note
 * The button supports hover and drag states, changing colors accordingly.
 * You should assign OnHold and OnClickFinished callbacks to handle button events.
 * The button can optionally display a texture.
 * Remember to call Update() every frame to process input and state changes,
 * and call Draw() to render the button.
 *
 * @example
 * Button myButton(
 *     RectanglePro{50, 50, 100, 40},  // button rectangle
 *     skin,                          // UISkin for button
 *     text,                          // TextPro for button label
 *     []() {  on hold callback code  },
 * []() {  on click finished callback code  }
 * );
 *
 *	 while (!WindowShouldClose())
 *   {
 *		myButton.Update();
 *		myButton.Draw();
 *
 *   }
 */

class Button : public UserInterface {
public:
	Button();
	Button(const RectanglePro& rect, const UISkin& skin, const TextPro& text);
	Button(const RectanglePro& rect, const UISkin& skin, const TextPro& text, ButtonCallback onHold,
		ButtonCallback onClickFinished);
	Button(const RectanglePro& rect, const UISkin& skin, const TextPro& text, ButtonCallback onHold,
		ButtonCallback onClickFinished, Texture2D texture);

	//Getters
	[[nodiscard]] bool isHovered() const { return m_hovered; }
	[[nodiscard]] bool isDragging() const { return m_isDragging; }
	[[nodiscard]] ButtonCallback getOnHold() const { return m_onHold; }
	[[nodiscard]] ButtonCallback getOnClickFinished() const { return m_onClickFinished; }

	//Setters
	void setOnHold(ButtonCallback onHold) { m_onHold = onHold; }
	void setOnClickFinished(ButtonCallback onClickFinished) { m_onClickFinished = onClickFinished; }
	void setBaseColor(Color baseColor) { m_baseColor = baseColor; }
	void setHoverColor(Color hoverColor) { m_hoverColor = hoverColor; }

	void Update() override;
	void Draw() override;
private:
	ButtonCallback m_onHold = [&]() {};
	ButtonCallback m_onClickFinished = [&]() {};

	void defaultOnHold();
	void defaultOnClickFinished();
	void resetToDefault();
	void safeInvoke(const ButtonCallback& callback);

	bool m_hovered = false;
	bool m_isDragging = false; 

	Vector2 m_baseSize = { 0, 0 };
	Color m_baseColor = DEFAULT_COLOR;
	Color m_hoverColor = DEFAULT_HOVER_COLOR;

	Texture2D m_texture = { 0 };
	bool m_hasTexture = false;

	static constexpr Color DEFAULT_COLOR = { 0, 122, 204, 255 };
	static constexpr Color DEFAULT_HOVER_COLOR = { 100, 170, 230, 255 };
	static constexpr Color HOLD_COLOR = { 0, 90, 158, 255 };
	static constexpr float SIZE_OFFSET_ON_HOLD = 10.0f;
};
