#pragma once

#include "../userInterface.h"

/**
* @brief Represents a button in the user interface.
*/
class Button : private UserInterface {
public:
	Button(RectanglePro rect);
	Button(RectanglePro rect, TextPro textInfo);
	//Button(Rectangle bounds, const char* text, Texture2D texture);
	void Update() override;
private:
	//const char* m_text;
	Texture2D m_texture = { 0 }; 
	bool m_isPressed = false;
	//void Draw() override;
	//void HandleInput() override;


};
