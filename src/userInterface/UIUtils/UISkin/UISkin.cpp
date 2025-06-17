#include "UISkin.h"

UISkin::UISkin()
    : m_color(WHITE), m_texture{}, m_hasTexture(false), m_segmentAmount(16)
{
}

UISkin::UISkin(Color color)
    : m_color(color), m_texture{}, m_hasTexture(false), m_segmentAmount(16)
{
}

UISkin::UISkin(const Texture2D& texture)
    : m_color(WHITE), m_segmentAmount(16)
{
    if (texture.id == 0)
    {
        m_texture = {0};
        m_hasTexture = false;
    }
    else
    {
        m_texture = texture;
        m_hasTexture = true;
    }
}

void UISkin::Draw(const RectanglePro& rect) const
{
    rlPushMatrix();

    Vector2 center = { rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f };
    rlTranslatef(center.x, center.y, 0.0f);
    rlRotatef(rect.getRotation(), 0.0f, 0.0f, 1.0f);
    if (m_hasTexture)
    {
        DrawTexturePro(
            m_texture,
            { 0, 0, (float)m_texture.width, (float)m_texture.height },
            { -rect.width / 2.0f, -rect.height / 2.0f, rect.width, rect.height },
            { 0, 0 },
            0.0f,
            m_color
        );
    }
    else
    {
        float normalizedRadius = rect.getCornerRadius() / std::min(rect.width, rect.height);
        normalizedRadius = std::clamp(normalizedRadius, 0.0f, 1.0f);

        DrawRectangleRounded(
            { -rect.width / 2.0f, -rect.height / 2.0f, rect.width, rect.height },
            normalizedRadius,
            m_segmentAmount,
            m_color);
    }

    rlPopMatrix();
}