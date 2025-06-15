#pragma once

#include <string>

#include "raylib.h"


/**
* @brief Represents a text object with additional properties
*/
class TextPro
{
public:
	TextPro();
	explicit TextPro(const std::string& text);
	TextPro(const std::string& text, Color color);
	TextPro(const std::string& text, Font font, int fontSize, Color color,
		    Vector2 position, Vector2 origin, float rotation, float spacing);
    
    void Draw();

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
	

private:

	static constexpr float DEFAULT_FONT_SIZE = 20.0f;
	static constexpr float DEFAULT_ROTATION = 0.0f;
	static constexpr float DEFAULT_SPACING = 1.5f;
    static constexpr Color DEFAULT_COLOR = WHITE;
	static constexpr Vector2 DEFAULT_POSITION = { 0, 0 };
	static constexpr Vector2 DEFAULT_ORIGIN = { 0, 0 };

    std::string m_text = "Default Text";
    Color m_color = WHITE;
    Vector2 m_position = { 0, 0 };
    Vector2 m_origin = { 0, 0 };
    float m_rotation = 0.0f;
    float m_spacing = 0.0f;
    float m_fontSize = 20.0f;
    Font m_font = GetFontDefault();

    void CenterOrigin();
};