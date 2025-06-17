#include "RectanglePro.h"

RectanglePro::RectanglePro()
	: RectanglePro({ 0, 0 }, { 100, 100 }, 0.0f, DEFAULT_CORNER_RADIUS) {
}

RectanglePro::RectanglePro(Vector2 centerPos, Vector2 size, float rotation,
    float cornerRadius)
    : Rectangle{ centerPos.x - size.x / 2.0f, centerPos.y - size.y / 2.0f,
                size.x, size.y },
    m_rotation(rotation), m_cornerRadius(cornerRadius)
{
	m_segmentAmount = DEFAULT_SEGMENT_AMOUNT;
}

Rectangle RectanglePro::getRectangle() const
{
    Vector2 pos = getPosition();
    Vector2 size = getSize();
    return Rectangle{ pos.x - (size.x / 2.0f), pos.y - (size.y / 2.0f), size.x, size.y };
}

void RectanglePro::setSize(Vector2 size) {
    Vector2 center = getPosition(); 
    width = size.x;
    height = size.y;
    setPosition(center);
}

void RectanglePro::setPosition(Vector2 position) {
    x = position.x - width / 2.0f;
    y = position.y - height / 2.0f;
}

void RectanglePro::setBounds(RectanglePro& bounds) {
    x = bounds.x;
    y = bounds.y;
    width = bounds.width;
    height = bounds.height;
}