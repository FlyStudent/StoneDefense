
#include "entity.h"
#include "component/collider.h"

Collider::Collider(Entity& en) 
: Component(en)
{}


void     Collider::setTag(uint64_t tag)
{
    m_tag = tag;
}

void     Collider::setMask(uint64_t mask)
{
    m_mask = mask;
}

int Collider::getTag() const
{
    return m_tag;
}

int Collider::getMask() const
{
    return m_mask;
}