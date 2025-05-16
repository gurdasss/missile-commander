#include <raylib.h>

#ifndef RECTANGLE_2D_H
#define RECTANGLE_2D_H

class Rectangle2D
{
public:
    void setPosition(const Vector2 &position);
    Vector2 getPosition() const;

    void setWidth(float width);
    float getWidth() const;

    void setHeight(float width);
    float getHeight() const;

    void setTint(const Color &tint);
    const Color &getTint() const;

    const Rectangle &getRectangle() const;

private:
    Rectangle m_rectangle{};
    Color m_tint{GRAY};
};

#endif