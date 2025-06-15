#include "RectanglePro.h"

RectanglePro::RectanglePro(Vector2 centerPos, Vector2 size, float rotation,
    float cornerRadius, Color color)
    : Rectangle{ centerPos.x - size.x / 2.0f, centerPos.y - size.y / 2.0f,
                size.x, size.y },
    m_rotation(rotation), m_cornerRadius(cornerRadius), m_color(color) {
}

void RectanglePro::Draw() {
    rlPushMatrix();

    Vector2 center = { x + width / 2, y + height / 2 };

    rlTranslatef(center.x, center.y, 0.0f);
    rlRotatef(m_rotation, 0.0f, 0.0f, 1.0f);

    float normalizedRadius =
        m_cornerRadius / std::min(width, height);
    if (normalizedRadius < 0.0f)
        normalizedRadius = 0.0f;
    if (normalizedRadius > 1.0f)
        normalizedRadius = 1.0f;

    DrawRectangleRounded(
        { -width / 2, -height / 2, width, height },
        normalizedRadius, DEFAULT_SEGMENT_AMOUNT, m_color);

    rlPopMatrix();
}