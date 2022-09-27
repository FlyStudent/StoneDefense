
#include "entity.h"

#include "primitive2.h"
#include "enums.h"
#include "component/box_collider.h"

BoxCollider::BoxCollider(Entity& en, Box box) :
 Collider(en),
 m_box(box) 
 {}

 void BoxCollider::update()
 {
     m_box.m_center = m_entity.m_pos;
 }

 void   BoxCollider::setRange(float w, float h)
 {
     m_box.m_halfWidth = w;
     m_box.m_halfHeight = h;
 }