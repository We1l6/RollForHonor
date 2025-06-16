#pragma once
#include <algorithm>
#include <cmath>

#include "raylib.h"
#include "rlgl.h"

/***
* @brief Represents a rectangle with rounded corners and rotation.
*/
class RectanglePro : public Rectangle
{
public:
	RectanglePro();
	RectanglePro(Vector2 centerPos, Vector2 size, float rotation,
		float cornerRadius, Color color);

	//Getters
	[[nodiscard]] float getRotation() const { return m_rotation; }
	[[nodiscard]] float getCornerRadius() const { return m_cornerRadius; }
	[[nodiscard]] Color getColor() const { return m_color; }
	[[nodiscard]] Vector2 getPosition() const { return { x + width / 2.0f, y + height / 2.0f }; }
	[[nodiscard]] Vector2 getSize() const { return { width, height }; }

	//Setters
	void setRotation(float rotation) { m_rotation = rotation; }
	void setCornerRadius(float cornerRadius) { m_cornerRadius = cornerRadius; }
	void setColor(Color color) { m_color = color; }
	void setSegmentAmount(int segmentAmount) { m_segmentAmount = std::max(segmentAmount, 3); }
	void setSize(Vector2 size);
	void setPosition(Vector2 position);
	void setBounds(RectanglePro& bounds);
	

	void Draw();
	
private:
	static constexpr int DEFAULT_SEGMENT_AMOUNT = 16; //Number of segments for rounded corners
	static constexpr float DEFAULT_CORNER_RADIUS = 0.0f; //Default corner radius
	static constexpr Color DEFAULT_COLOR = WHITE; //Default color

	int m_segmentAmount;
	float m_rotation;
	float m_cornerRadius;
	Color m_color;
};