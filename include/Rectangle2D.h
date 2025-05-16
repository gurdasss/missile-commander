#include <raylib.h>

#ifndef RECTANGLE_2D_H
#define RECTANGLE_2D_H

class Rectangle2D
{
public:
    /*
        compiler will not generate an implicit default constructor
        if a user defined constructor already exist. As a result,
        we're explicitly asking the compiler to generate a default
        constructor for us.
    */
    Rectangle2D() = default;
    Rectangle2D(float width, float height);

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