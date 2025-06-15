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
	Button(const RectanglePro& rect, const TextPro& text);
	Button(const RectanglePro& rect, const TextPro& text, ButtonCallback onHold,
		ButtonCallback onClickFinished);

	//Getters
	[[nodiscard]] bool isHovered() const { return m_hovered; }
	[[nodiscard]] Texture2D getTexture() const { return m_texture; }

	//Setters
	void setTexture(Texture2D texture) { m_texture = texture; }
	void setOnHold(ButtonCallback onHold) { m_onHold = onHold; }
	void setOnClickFinished(ButtonCallback onClickFinished) { m_onClickFinished = onClickFinished; }
	void setColor(Color color) { m_rect.setColor(color); }

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

	Vector2 m_baseSize = { 0, 0 };

	Texture2D m_texture = { 0 }; 

	static constexpr Color DEFAULT_COLOR = { 0, 122, 204, 255 };
	static constexpr Color HOVER_COLOR = { 100, 170, 230, 255 };
	static constexpr Color HOLD_COLOR = { 0, 90, 158, 255 };
	static constexpr float SIZE_OFFSET_ON_HOLD = 10.0f;
};
