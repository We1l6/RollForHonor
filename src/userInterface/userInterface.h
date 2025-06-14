#pragma once

#include <string>
#include <cmath>
#include <algorithm> 

#include "raylib.h"
#include "rlgl.h"

#include "UIUtils.h"


class UserInterface {
protected:
	inline static const int DEFAULT_FONT_SIZE = 20; 
	TextPro m_text;
	RectanglePro m_rect;

	UserInterface(RectanglePro rect);
	UserInterface(RectanglePro rect, TextPro text);




public:
	virtual ~UserInterface() = default;
	// Getters
	RectanglePro GetBounds() const { return m_rect; }
	int GetWidth() const { return static_cast<int>(m_rect.width); }
	int GetHeight() const { return static_cast<int>(m_rect.height); }
	int GetX() const { return static_cast<int>(m_rect.x); }
	int GetY() const { return static_cast<int>(m_rect.y); }
	// Setters
	void SetBounds(RectanglePro bounds) { m_rect = bounds; }
	void SetPosition(int x, int y) { m_rect.x = static_cast<float>(x); m_rect.y = static_cast<float>(y); }

	//bool isHovered() const { return m_isHovered; }

	virtual void Draw();
	virtual void Update();
	virtual void HandleInput(); 

private:
	/*bool m_isHovered = false;
	bool m_isPressed = false;*/
};



