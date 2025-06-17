/**
 * @file UISkin.h
 * @brief UI skin class for visual styling of interface elements
 * @details
 * Encapsulates visual properties including color, texture, and segment detail used for rendering UI components.
 * Supports initialization with either a solid color or a texture.
 * Provides getters and setters to access and modify skin properties.
 * The Draw() method renders the skin on a specified RectanglePro area.
 *
 * @author koliruslik
 * @date 17/06/2025
 */

#pragma once


#include "raylib.h"
#include "rlgl.h"
#include "../RectanglePro/RectanglePro.h"
#include <algorithm>


/**
 * @brief UISkin class represents the visual style of UI elements.
 *
 * Encapsulates color, texture, and segment amount for rendering UI components.
 *
 * Constructors allow initialization with a color or texture.
 *
 * Getters and setters provide access to and modification of the skin properties.
 *
 * The Draw() method renders the skin onto a given RectanglePro area.
 */
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
	void setTexture(Texture2D texture) { m_texture = texture; }
	void clearTexture() { m_hasTexture = false; }
	void setSegmentAmount(int amount) { m_segmentAmount = std::max(amount, 3); }

	void Draw(const RectanglePro& rect) const;

private:
	Color m_color;
	Texture2D m_texture;
	bool m_hasTexture;
	int m_segmentAmount;
};