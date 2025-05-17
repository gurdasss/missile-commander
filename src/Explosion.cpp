#include "Explosion.h"
#include "Circle2D.h"

// Explosion::Explosion is a delegating constructor
// calling Circle2D::Circle2D(const Vector2 &position, float radius)
Explosion::Explosion(const Vector2 &position, float radius)
    : Circle2D{position, radius}
{
}

void Explosion::setGrow(float grow) { m_grow = grow; }
float Explosion::getGrow() const { return m_grow; }