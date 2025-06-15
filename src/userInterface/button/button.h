#pragma once

#include <functional>

#include "../userInterface.h"


//std::function<void()> is a type alias for a function that takes no arguments and returns void.
using ButtonCallback = std::function<void()>;

/**
* @brief Represents a button in the user interface.
*/
class Button : public UserInterface {
public:
	Button();
	Button(const RectanglePro& rect, const TextPro& text);
	Button(const RectanglePro& rect, const TextPro& text, ButtonCallback onHold,
		ButtonCallback onClickFinished);

	//Getters
	[[nodiscard]] bool isHovered() const { return m_hovered; }
	[[nodiscard]] bool isDragging() const { return m_isDragging; }
	[[nodiscard]] ButtonCallback getOnHold() const { return m_onHold; }
	[[nodiscard]] ButtonCallback getOnClickFinished() const { return m_onClickFinished; }
	[[nodiscard]] Color getColor() const { return m_rect.getColor(); }

	//Setters
	void setTexture(Texture2D texture) { m_texture = texture; }
	void setOnHold(ButtonCallback onHold) { m_onHold = onHold; }
	void setOnClickFinished(ButtonCallback onClickFinished) { m_onClickFinished = onClickFinished; }
	void setColor(Color color) { m_rect.setColor(color); }
	void setBaseColor(Color baseColor) { m_baseColor = baseColor; }
	void setHoverColor(Color hoverColor) { m_hoverColor = hoverColor; }

	void Update() override;
private:
	//Lambda functions for Hold and Click events
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

	static constexpr Color DEFAULT_COLOR = { 0, 122, 204, 255 };
	static constexpr Color DEFAULT_HOVER_COLOR = { 100, 170, 230, 255 };
	static constexpr Color HOLD_COLOR = { 0, 90, 158, 255 };
	static constexpr float SIZE_OFFSET_ON_HOLD = 10.0f;
};
