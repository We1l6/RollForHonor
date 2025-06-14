#pragma once

#include <functional>

#include "../userInterface.h"

//std::function<void()> is a type alias for a function that takes no arguments and returns void.
using ButtonCallback = std::function<void()>;
/**
* @brief Represents a button in the user interface.
*/
class Button : private UserInterface {
public:
	Button(const RectanglePro& rect, const TextPro& text);
	Button(const RectanglePro& rect, const TextPro& text, ButtonCallback onClick,
		ButtonCallback onRelease);

	//Button(Rectangle bounds, const char* text, Texture2D texture);
	void Update() override;

	//Getters
	[[nodiscard]] bool isHovered() const { return m_hovered; }
	[[nodiscard]] Texture2D getTexture() const { return m_texture; }

	//Setters
	void setTexture(Texture2D texture) { m_texture = texture; }
	void setOnClick(ButtonCallback onClick) { m_onClick = onClick; }
	void setOnRelease(ButtonCallback onRelease) { m_onRelease = onRelease; }
	void setColor(Color color) { m_rect.setColor(color); }
private:
	static constexpr Color DEFAULT_COLOR = BLUE;
	static constexpr Color CLICK_COLOR = BLACK;
	static constexpr Color HOVER_COLOR = LIGHTGRAY;

	//Lambda functions for click and release events
	ButtonCallback m_onClick = [&]() {};
	ButtonCallback m_onRelease = [&]() {};

	bool m_hovered = false;
	Vector2 mousePosition = { 0, 0 };
	Texture2D m_texture = { 0 }; 

//Immediate Mode
};
