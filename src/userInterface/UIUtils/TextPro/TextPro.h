/**
 * @file TextPro.h
 * @brief Advanced text rendering class with rotation and origin control
 * @details
 * Manages text display with customizable font, size, color, spacing, rotation, and origin.
 * Automatically recenters the origin when text, font, or font size changes.
 * The origin affects rotation and positioning of the text.
 * Draw() must be called each frame to render the text.
 *
 * @author koliruslik
 * @date 15/06/2025
 */

#pragma once

#include <string>

#include "raylib.h"

/**
 * @note
 * Changing the text, font, or font size will automatically recenter the origin.
 * The origin point affects the rotation and positioning of the text.
 * Make sure to call Draw() to render the text each frame after updating properties.
 *
 * @example
 * TextPro label("Hello, world!", BLACK);
 * label.setPosition({100, 50});
 * label.setFontSize(30.0f);
 * label.setRotation(15.0f);
 *
 * while (!WindowShouldClose())
 * {
 *     BeginDrawing();
 *     ClearBackground(RAYWHITE);
 *     label.Draw();
 *     EndDrawing();
 * }
 */
class TextPro
{
public:
	TextPro();
	explicit TextPro(const std::string& text);
	TextPro(const std::string& text, Color color);
	TextPro(const std::string& text, Font font, float fontSize, Color color,
		    Vector2 position, Vector2 origin, float rotation, float spacing);
    
    //Getters
	[[nodiscard]] std::string getText() const { return m_text; }
	[[nodiscard]] Color getColor() const { return m_color; }
	[[nodiscard]] Vector2 getPosition() const { return m_position; }
	[[nodiscard]] Vector2 getOrigin() const { return m_origin; }
	[[nodiscard]] float getRotation() const { return m_rotation; }
	[[nodiscard]] float getSpacing() const { return m_spacing; }
	[[nodiscard]] float getFontSize() const { return m_fontSize; }
	[[nodiscard]] Font getFont() const { return m_font; }

    //Setters
	void setText(const std::string& text) { m_text = text; CenterOrigin(); }
	void setColor(Color color) { m_color = color; }
	void setPosition(Vector2 position) { m_position = position; }
	void setOrigin(Vector2 origin) { m_origin = origin; }
	void setRotation(float rotation) { m_rotation = rotation; }
	void setSpacing(float spacing) { m_spacing = spacing; }
	void setFontSize(float fontSize) { m_fontSize = fontSize; CenterOrigin(); }
	void setFont(Font font) { m_font = font; CenterOrigin(); }
	
	void Draw();
private:

	static constexpr float DEFAULT_FONT_SIZE = 20.0f;
	static constexpr float DEFAULT_ROTATION = 0.0f;
	static constexpr float DEFAULT_SPACING = 1.5f;
    static constexpr Color DEFAULT_COLOR = BLACK;
	static constexpr Vector2 DEFAULT_POSITION = { 0, 0 };
	static constexpr Vector2 DEFAULT_ORIGIN = { 0, 0 };

    std::string m_text = "Default Text";
    Color m_color;
    Vector2 m_position;
    Vector2 m_origin;
    float m_rotation;
    float m_spacing;
    float m_fontSize;
    Font m_font = GetFontDefault();

    void CenterOrigin();
};