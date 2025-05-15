#include "Line2D.h"
#include <raylib.h>

void Line2D::setStartPos(const Vector2 &position) { m_startPos = position; }
const Vector2 &Line2D::getStartPos() const { return m_startPos; }

void Line2D::setEndPos(const Vector2 &position) { m_endPos = position; }
const Vector2 &Line2D::getEndPos() const { return m_endPos; }

void Line2D::setTint(const Color &tint) { m_tint = tint; }
const Color &Line2D::getTint() const { return m_tint; }
