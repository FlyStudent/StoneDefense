
#include <iostream>

#include "entity.h"
#include "enums.h"

#include "collision_engine.h"

#include "primitive2.h"
#include "component/collider.h"
#include "component/box_collider.h"
#include "component/circle_collider.h"

CollisionEngine::~CollisionEngine()
{
    m_colliders.clear();
}

void    CollisionEngine::setCollider(Collider* collider)
{
    m_colliders.push_back(collider);
}

void    CollisionEngine::setWaitingCollider(Collider* collider)
{
    m_waitingList.push_back(collider);
}

void    CollisionEngine::collisionCheck(Collider& colliderA, Collider& colliderB)
{
    bool isCollision = false;
    BoxCollider* boxA = dynamic_cast<BoxCollider*>(&colliderA);
    BoxCollider* boxB = dynamic_cast<BoxCollider*>(&colliderB);
    CircleCollider* circleA = dynamic_cast<CircleCollider*>(&colliderA);
    CircleCollider* circleB = dynamic_cast<CircleCollider*>(&colliderB);

    if (colliderA.getTag() == 256 || colliderB.getTag() == 256u)
        int x = 0;
    if (colliderA.getTag() == ColliderTag::TOWER_EXPLOSION)
        int i = 0;

    if (boxA && boxB)
        isCollision = boxsCollide(boxA->m_box, boxB->m_box);
    else if (boxA && circleB)
        isCollision = circleBoxCollide(circleB->m_circle, boxA->m_box);
    else if (boxB && circleA)
        isCollision = circleBoxCollide(circleA->m_circle, boxB->m_box);
    else if (circleA && circleB)
        isCollision = circlesCollide(circleA->m_circle, circleB->m_circle);
    if (isCollision)
    {
        colliderA.m_entity.collisionHappens(colliderB);
        colliderB.m_entity.collisionHappens(colliderA);
    }
}

void    CollisionEngine::update()
{
    int stop = 0;
    int size = m_colliders.size()-1;
    for (int i = 0; i <= size; ++i)
    {
        auto& colliderA = m_colliders[i];

        if (!colliderA->m_entity.m_isAlive)
            m_eraseList.push_back(i);

        for (int j = size; j >= stop+1; --j)
        {
            auto& colliderB = m_colliders[j]; 

            if (!colliderB->m_entity.m_isAlive)
                continue;

            if ( colliderA->m_isActivate && colliderB->m_isActivate 
                && (colliderA->getTag() & colliderB->getMask()))
            {
                collisionCheck(*colliderA, *colliderB);
            }
        }
        ++stop;
    }

    while ( m_waitingList.size() > 0)
    {
        auto& waiting = m_waitingList[m_waitingList.size()-1];
        m_colliders.emplace_back(std::move(waiting));
        m_waitingList.pop_back();
    }
    while ( m_eraseList.size() > 0)
    {
        m_colliders.erase(m_colliders.begin() + m_eraseList[m_eraseList.size()-1]);
        m_eraseList.pop_back();
    }
}