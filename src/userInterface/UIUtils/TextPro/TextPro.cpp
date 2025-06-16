#include "TextPro.h"

TextPro::TextPro() : TextPro("") {}

TextPro::TextPro(const std::string& text) : TextPro(text, m_color) {}

TextPro::TextPro(const std::string& text, Color color)
    : TextPro(text, GetFontDefault(), DEFAULT_FONT_SIZE, DEFAULT_COLOR, DEFAULT_POSITION, 
             DEFAULT_ORIGIN, DEFAULT_ROTATION, DEFAULT_SPACING) { }

TextPro::TextPro(const std::string& text, Font font, float fontSize, Color color,
    Vector2 position, Vector2 origin, float rotation, float spacing)
    : m_text(text), m_font(font), m_fontSize(fontSize), m_color(color),
    m_position(position), m_origin(origin), m_rotation(rotation), m_spacing(spacing) 
{
    CenterOrigin();
}

void TextPro::Draw() {
    DrawTextPro(m_font, m_text.c_str(), m_position,
        m_origin, m_rotation,
        m_fontSize, m_spacing,
        m_color);
}

void TextPro::CenterOrigin() {
    if (m_text.empty()) {
        m_origin = { 0, 0 };
        return;
    }
    Vector2 size = MeasureTextEx(m_font, m_text.c_str(), m_fontSize, m_spacing);
    m_origin = { size.x / 2.0f, size.y / 2.0f };
}