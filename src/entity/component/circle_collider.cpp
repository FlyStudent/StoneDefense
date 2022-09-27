
#include "entity.h"

#include "primitive2.h"
#include "enums.h"
#include "component/circle_collider.h"

CircleCollider::CircleCollider(Entity& en, Circle collider)
: Collider(en), m_circle(collider) {}

 void CircleCollider::update()
 {
     m_circle.m_center = m_entity.m_pos;
 }

 void   CircleCollider::setRange(float radius)
 {
     m_circle.m_radius = radius;
 }