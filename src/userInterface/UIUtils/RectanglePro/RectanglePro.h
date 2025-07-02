/**
 * @file RectanglePro.h
 * @brief Extended rectangle shape class with rotation and rounded corners.
 *
 * Defines a rectangle with additional properties such as rotation, corner radius, and segment detail
 * for smooth rounded edges. It provides getter and setter methods for position, size, rotation, and
 * rounding configuration. Inherits from raylib's Rectangle and extends its functionality to support
 * more advanced UI rendering use cases.
 *
 * @note This class only defines the shape properties and geometry.
 * It does not provide built-in rendering or drawing logic beyond Draw(), which is implementation-dependent.
 *
 * @example
 * RectanglePro rect({ 200, 200 }, { 100, 50 }, 15.0f, 8.0f);
 * rect.setSegmentAmount(12);
 * rect.Draw();
 *
 * @author koliruslik
 * @date 15/06/2025
 */

#pragma once

#include <algorithm>
#include <cmath>

#include "raylib.h"

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
	[[nodiscard]] Vector2 getSize() const { return { width, height }; }
	/**
	* @brief Get the center position of the rectangle.
	*/
	[[nodiscard]] Vector2 getPosition() const { return { x + width / 2.0f, y + height / 2.0f }; }
	/**
	* @brief Get the origin of the rectangle(top left).
	*/
	[[nodiscard]] Vector2 getOrigin() const { return { x, y }; }

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