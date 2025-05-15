#include <raylib.h>

#ifndef RECTANGLE_2D_H
#define RECTANGLE_2D_H

class Rectangle2D
{
public:
    Rectangle2D(float width, float height);

    void setPosition(const Vector2 &position);
    Vector2 getPosition() const;

    float getWidth() const;
    float getHeight() const;

    void setTint(const Color &tint);
    const Color &getTint() const;

    const Rectangle &getRectangle() const;

private:
    Rectangle m_rectangle{};
    Color m_tint{GRAY};
};

#endif