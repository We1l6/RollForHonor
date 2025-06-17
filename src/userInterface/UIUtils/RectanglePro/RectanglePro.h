/**
 * @file RectanglePro.h
 * @brief Extended rectangle shape class with rotation and rounded corners
 * @details
 * Defines a rectangle shape with additional properties such as rotation and corner radius.
 * Does not provide built-in rendering; only geometry and shape data are handled.
 * Supports customization of corner rounding and segment detail for smoothness.
 * Provides getters and setters for size, position, rotation, and corner radius.
 * Draw() can be called to render the shape (implementation-dependent).
 *
 * @author koliruslik
 * @date 15/06/2025
 */

#pragma once

#include <algorithm>
#include <cmath>

#include "raylib.h"

/***
 * @note This class only defines the shape properties and geometry.
 * It does not provide built-in rendering or drawing capabilities.
 */
class RectanglePro : public Rectangle
{
public:
	RectanglePro();
	RectanglePro(Vector2 centerPos, Vector2 size, float rotation,
		float cornerRadius);

	//Getters
	[[nodiscard]] Rectangle getRectangle() const;
	[[nodiscard]] float getRotation() const { return m_rotation; }
	[[nodiscard]] float getCornerRadius() const { return m_cornerRadius; }
	[[nodiscard]] Vector2 getPosition() const { return { x + width / 2.0f, y + height / 2.0f }; }
	[[nodiscard]] Vector2 getSize() const { return { width, height }; }
	[[nodiscard]] Vector2 getOrigin() const { return { getSize().x / 2.0f, getSize().y / 2.0f }; }

	//Setters
	void setRotation(float rotation) { m_rotation = rotation; }
	void setCornerRadius(float cornerRadius) { m_cornerRadius = cornerRadius; }
	void setSegmentAmount(int segmentAmount) { m_segmentAmount = std::max(segmentAmount, 3); }
	void setSize(Vector2 size);
	void setPosition(Vector2 position);
	void setBounds(RectanglePro& bounds);
		
	void Draw();
private:
	static constexpr int DEFAULT_SEGMENT_AMOUNT = 16;
	static constexpr float DEFAULT_CORNER_RADIUS = 0.0f;

	int m_segmentAmount;
	float m_rotation;
	float m_cornerRadius;
};