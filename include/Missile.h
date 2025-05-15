#include "Line2D.h"
#include <raylib.h>

#ifndef MISSILE_H
#define MISSILE_H

class Missile : public Line2D
{
public:
    void setMissileDistance(float distance);
    void updateMissileDistance(float distance);
    float getMissileDistance() const;

    void setMissileSpeed(float speed);
    float getMissileSpeed() const;

    void setTargetPos(const Vector2 &position);
    const Vector2 &getTargetPos() const;

private:
    float m_missileDistance{};
    Vector2 m_targetPos{};
    float m_missileSpeed{};
};

#endif