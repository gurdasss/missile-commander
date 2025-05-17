#include "Circle2D.h"
#include <raylib.h>

#ifndef EXPLOSION_H
#define EXPLOSION_H

class Explosion : public Circle2D
{
public:
    Explosion(const Vector2 &position, float radius);

    void setGrow(float grow);
    float getGrow() const;

private:
    float m_grow{1.0f};
};

#endif