#pragma once
#include "raylib.h"
#include "rlgl.h"
#include <algorithm>
#include <cmath>
#include <string>

struct RectanglePro : Rectangle {
  int segments = 16; // Number of segments for rounded corners

  float rotation;
  float cornerRadius;
  Color color;

  RectanglePro(Vector2 _centerPos, Vector2 _size, float _rotation,
               float _cornerRadius, Color _color)
      : Rectangle{_centerPos.x - _size.x / 2.0f, _centerPos.y - _size.y / 2.0f,
                  _size.x, _size.y},
        rotation(_rotation), cornerRadius(_cornerRadius), color(_color) {}
};

struct TextPro {
  std::string text = "Default Text";
  Font font = GetFontDefault();
  int fontSize = 20;
  Color color = WHITE;
  Vector2 position = {0, 0};
  Vector2 origin = {0, 0};
  float rotation = 0.0f;
  float spacing = 0.0f;

  TextPro()
      : text("Default Text"), font(GetFontDefault()), fontSize(20),
        color(WHITE), position({0, 0}), origin({0, 0}), rotation(0.0f),
        spacing(0.0f) {}

  // text constructor
  explicit TextPro(const std::string &_text)
      : text(_text), font(GetFontDefault()), fontSize(20), color(WHITE),
        position({0, 0}), origin({0, 0}), rotation(0.0f), spacing(0.0f) {}

  // text and color constructor
  TextPro(const std::string &_text, Color _color)
      : text(_text), font(GetFontDefault()), fontSize(20), color(_color),
        position({0, 0}), origin({0, 0}), rotation(0.0f), spacing(0.0f) {}

  // full constructor
  TextPro(const std::string &_text, Font _font, int _fontSize, Color _color,
          Vector2 _position, Vector2 _origin, float _rotation, float _spacing)
      : text(_text), font(_font), fontSize(_fontSize), color(_color),
        position(_position), origin(_origin), rotation(_rotation),
        spacing(_spacing) {}
  /**
   * Centers the origin of the text based on its length and font size.
   * This is useful for aligning text in the center of a rectangle or screen.
   */
  void CenterOrigin() {
    int baseTextWidth = MeasureText(text.c_str(), fontSize);
    int textLength = static_cast<int>(text.length());

    float totalSpacing = 0.0f;
    if (textLength > 1) {
      totalSpacing = (textLength - 1) * spacing * fontSize;
    }

    float totalTextWidth = baseTextWidth + totalSpacing;
    int textHeight = fontSize;

    origin = {totalTextWidth / 2.0f, textHeight / 2.0f};
  }
};

namespace UIUtils {
/**
 * Draws a rectangle with rounded corners.
 * @param rect The rectangle to draw.
 * @param radius The radius of the rounded corners (0.0f for no rounding).
 * @param segments The number of segments for the rounded corners.
 * @param color The color of the rectangle.
 */
inline void DrawRectangleProRounded(const RectanglePro &rect) {
  rlPushMatrix();

  Vector2 center = {rect.x + rect.width / 2, rect.y + rect.height / 2};

  rlTranslatef(center.x, center.y, 0.0f);
  rlRotatef(rect.rotation, 0.0f, 0.0f, 1.0f);

  float normalizedRadius =
      rect.cornerRadius / std::min(rect.width, rect.height);
  if (normalizedRadius < 0.0f)
    normalizedRadius = 0.0f;
  if (normalizedRadius > 1.0f)
    normalizedRadius = 1.0f;

  DrawRectangleRounded(
      {-rect.width / 2, -rect.height / 2, rect.width, rect.height},
      normalizedRadius, rect.segments, rect.color);

  rlPopMatrix();
}

inline void DrawTextPro(const TextPro &textPro) {
  DrawTextPro(textPro.font, textPro.text.c_str(), textPro.position,
              textPro.origin, textPro.rotation,
              static_cast<float>(textPro.fontSize), textPro.spacing,
              textPro.color);
}

} // namespace UIUtils
