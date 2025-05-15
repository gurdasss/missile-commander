#include <raylib.h>

#ifndef LINE_2D_H
#define LINE_2D_H

class Line2D
{
public:
    void setStartPos(const Vector2 &position);
    const Vector2 &getStartPos() const;

    void setEndPos(const Vector2 &position);
    const Vector2 &getEndPos() const;

    void setTint(const Color &tint);
    const Color &getTint() const;

private:
    Vector2 m_startPos{};
    Vector2 m_endPos{};
    Color m_tint{RED};
};

#endif