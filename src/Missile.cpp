#include "Missile.h"
#include <raylib.h>

void Missile::setMissileDistance(float distance) { m_missileDistance = distance; }
void Missile::updateMissileDistance(float distance) { m_missileDistance += distance; }
float Missile::getMissileDistance() const { return m_missileDistance; }

void Missile::setMissileSpeed(float speed) { m_missileSpeed = speed; }
float Missile::getMissileSpeed() const { return m_missileSpeed; }

void Missile::setTargetPos(const Vector2 &position) { m_targetPos = position; }
const Vector2 &Missile::getTargetPos() const { return m_targetPos; }