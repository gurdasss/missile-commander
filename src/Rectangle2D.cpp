#include "Rectangle2D.h"
#include <raylib.h>

Rectangle2D::Rectangle2D(float width, float height)
    : m_rectangle{0, 0, width, height}
{
    // a constructor's body is typically left empty.
}

void Rectangle2D::setPosition(const Vector2 &position)
{
    m_rectangle.x = position.x;
    m_rectangle.y = position.y;
}

Vector2 Rectangle2D::getPosition() const
{
    return Vector2{m_rectangle.x, m_rectangle.y};
}

void Rectangle2D::setWidth(float width) { m_rectangle.width = width; }
float Rectangle2D::getWidth() const { return m_rectangle.width; }

void Rectangle2D::setHeight(float height) { m_rectangle.height = height; }
float Rectangle2D::getHeight() const { return m_rectangle.height; }

void Rectangle2D::setTint(const Color &tint) { m_tint = tint; }
const Color &Rectangle2D::getTint() const { return m_tint; }

const Rectangle &Rectangle2D::getRectangle() const { return m_rectangle; }