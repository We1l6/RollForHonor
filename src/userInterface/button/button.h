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
	Button(const RectanglePro& rect, const TextPro& text, ButtonCallback onHold,
		ButtonCallback onClickFinished);

	//Button(Rectangle bounds, const char* text, Texture2D texture);
	void Update() override;

	//Getters
	[[nodiscard]] bool isHovered() const { return m_hovered; }
	[[nodiscard]] Texture2D getTexture() const { return m_texture; }

	//Setters
	void setTexture(Texture2D texture) { m_texture = texture; }
	void setOnHold(ButtonCallback onHold) { m_onHold = onHold; }
	void setOnClickFinished(ButtonCallback onClickFinished) { m_onClickFinished = onClickFinished; }
	void setColor(Color color) { m_rect.setColor(color); }
private:
	static constexpr Color DEFAULT_COLOR = { 0, 122, 204, 255 }; 
	static constexpr Color HOVER_COLOR = { 100, 170, 230, 255 };
	static constexpr Color HOLD_COLOR = { 0, 90, 158, 255 }; 

	//Lambda functions for click and release events
	ButtonCallback m_onHold = [&]() {};
	ButtonCallback m_onClickFinished = [&]() {};

	bool m_hovered = false;
	Vector2 mousePosition = { 0, 0 };
	Texture2D m_texture = { 0 }; 

//Immediate Mode
};
