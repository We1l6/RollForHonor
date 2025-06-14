#include "button.h"
Button::Button(RectanglePro rect)
	: UserInterface(rect)
{
}
Button::Button(RectanglePro rect, TextPro text)
	: UserInterface(rect, text)
{
}
void Button::Update()
{
	// Check if the button is hovered or pressed
	/*m_isHovered = UserInterfaceUtils::IsMouseOverRectangle(m_rect);
	m_isPressed = UserInterfaceUtils::IsMousePressedOnRectangle(m_rect);*/
	// Draw the button
	this->Draw();
}