/**
 * @file UISkin.h
 * @brief UI skin class for visual styling of interface elements.
 *
 * Encapsulates visual properties including color, texture, and segment detail used for rendering UI components.
 * Supports initialization with either a solid color or a texture. Provides getters and setters to access and modify
 * skin properties such as color, texture, and segment amount. The Draw() method renders the skin onto a specified
 * RectanglePro area using raylib and rlgl.
 *
 * @note setSegmentAmount() clamps values to a minimum of 3. Use clearTexture() to disable texture usage.
 *
 * @example
 * UISkin skin(BLUE);
 * RectanglePro rect(100, 100, 200, 50);
 *
 * while (!WindowShouldClose())
 * {
 *     BeginDrawing();
 *     ClearBackground(RAYWHITE);
 *     skin.Draw(rect);
 *     EndDrawing();
 * }
 *
 * @author koliruslik
 * @date 17/06/2025
 */

#pragma once


#include "raylib.h"
#include "rlgl.h"
#include "../RectanglePro/RectanglePro.h"
#include <algorithm>

class UISkin
{
public:
	UISkin();
	UISkin(Color color);
	UISkin(const Texture2D& texture);

	//Getters
	[[nodiscard]] Color getColor() const { return m_color; }
	[[nodiscard]] Texture2D getTexture() const { return m_texture; }
	[[nodiscard]] int getSegmentAmount() const { return m_segmentAmount; }

	//Setters
	void setColor(Color color) { m_color = color; }
	void setTexture(Texture2D texture) { m_texture = texture; m_hasTexture = true; }
	void clearTexture() { m_hasTexture = false; }
	void setSegmentAmount(int amount) { m_segmentAmount = std::max(amount, 3); }

	void Draw(const RectanglePro& rect) const;

private:
	Color m_color;
	Texture2D m_texture;
	bool m_hasTexture;
	int m_segmentAmount;
};