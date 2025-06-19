/**
 * @file TextBox.h
 * @brief Multi-line animated text box with automatic word wrapping
 * @details
 * Handles rich text display with animation, customizable font, colors, spacing, and layout.
 * Text is automatically wrapped to fit within a specified width.
 * Supports animated character-by-character drawing, as well as instant reveal.
 * Designed for use with Raylib and a Button-based visual container.
 *
 * @note
 * Call setText() to assign content. Draw() renders the full text immediately,
 * while DrawAnimated() progressively displays it by character.
 * Use skipAnimation() to instantly reveal the entire text.
 * Ensure Update() is called each frame when using animation.
 *
 * @example
 * TextBox dialog("Welcome to the game!");
 * dialog.setFont(myFont);
 * dialog.setTextColor(BLACK);
 *
 * while (!WindowShouldClose())
 * {
 *     dialog.Update();
 *
 *     BeginDrawing();
 *     ClearBackground(RAYWHITE);
 *     dialog.DrawAnimated(); // or dialog.Draw();
 *     EndDrawing();
 * }
 *
 * @author koliruslik
 * @date 19/06/2025
 */


#pragma once

#include "raylib.h"

#include "../../Button/Button.h"

#include <string>
#include <vector>
#include <sstream>
class TextBox
{
public:
	TextBox(const std::string text);
	TextBox(const std::string text, const RectanglePro& rect, const UISkin& skin);

	//Getters
	//std::string getText();

	//Setters
	void setText(std::string text);
	void setFont(Font font) { m_font = font; }
	void setColor(Color color) { m_textBoxButton.setBaseColor(color); m_textBoxButton.setHoverColor(color); }
	void setTextColor(Color color) { m_textColor = color; }

	void Draw();
	void Update();
	void DrawAnimated();
private:
	std::vector<std::string> m_lines;
	Button m_textBoxButton;

	float m_fontSize;
	float m_maxWidth;
	float m_spacing;
	float m_lineSpacing;
	float m_timer;
	float m_charDelay;
	float m_charSpacing;
	int m_visibleChars;
	Vector2 m_position;
	Font m_font;
	Color m_textColor;
	Color m_holdColor;

	void wrapTextToLines(std::string text);
	int getTotalCharCount() const;
	void skipAnimation();

	static constexpr float DEFAULT_FONT_SIZE = 20.0f;
	static constexpr float DEFAULT_SPACING = 2.0f;
	static constexpr float DEFAULT_LINE_SPACING = DEFAULT_FONT_SIZE + 5.0f;
	static constexpr float DEFAULT_CHAR_SPACING = 1.5f;
	static constexpr float DEFAULT_TIMER = 0.0f;
	static constexpr float DEFAULT_CHARS_DELAY = 0.05f;
	static constexpr int DEFAULT_VISIBLE_CHARS = 0;
	static constexpr Color DEFAULT_COLOR = { 0, 0, 0,128 };
	static constexpr Color DEFAULT_HOLD_COLOR = { 0, 0, 0,100 };
	static constexpr Color DEFAULT_TEXT_COLOR = BLACK;
};