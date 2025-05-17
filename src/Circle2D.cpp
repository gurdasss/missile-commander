#include "Circle2D.h"
#include <raylib.h>

Circle2D::Circle2D(const Vector2 &position, float radius)
    : m_center{position},
      m_radius{radius}
{
}

void Circle2D::setPosition(const Vector2 &position) { m_center = position; }
const Vector2 &Circle2D::getPosition() const { return m_center; }

void Circle2D::setRadius(float radius) { m_radius = radius; }
float Circle2D::getRadius() const { return m_radius; }

void Circle2D::setTint(const Color &tint) { m_tint = tint; }
const Color &Circle2D::getTint() const { return m_tint; }