#pragma once
#include <algorithm>
#include <cmath>

#include "raylib.h"
#include "rlgl.h"

class RectanglePro : public Rectangle
{
public:
	
	RectanglePro(Vector2 centerPos, Vector2 size, float rotation,
		float cornerRadius, Color color);

	//Getters
	[[nodiscard]] float getRotation() const { return m_rotation; }
	[[nodiscard]] float getCornerRadius() const { return m_cornerRadius; }
	[[nodiscard]] Color getColor() const { return m_color; }	

	//Setters
	void setRotation(float rotation) { m_rotation = rotation; }
	void setCornerRadius(float cornerRadius) { m_cornerRadius = cornerRadius; }
	void setColor(Color color) { m_color = color; }
	void setBounds(RectanglePro bounds) {
		x = bounds.x;
		y = bounds.y;
		width = bounds.width;
		height = bounds.height;
	}

	void Draw();
	
private:
	const int DEFAULT_SEGMENT_AMOUNT = 16; // Number of segments for rounded corners
	float m_rotation;
	float m_cornerRadius;
	Color m_color;
};