#include <raylib.h>

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle2D
{
public:
    /*
        compiler will not generate an implicit default constructor
        if a user defined constructor already exist. As a result,
        we're explicitly asking the compiler to generate a default
        constructor for us.
    */
    Circle2D() = default;
    Circle2D(const Vector2 &position, float radius);

    void setPosition(const Vector2 &position);
    const Vector2 &getPosition() const;

    void setRadius(float radius);
    float getRadius() const;

    void setTint(const Color &tint);
    const Color &getTint() const;

private:
    Vector2 m_center{};
    float m_radius{};
    Color m_tint{RED};
};

#endif