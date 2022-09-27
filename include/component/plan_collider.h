#pragma once

#include "component.h"

class Entity;

class PlanCollider : public Component
{
private:

public:
    PlanCollider(Entity&);
    ~PlanCollider() = default;
    
    void    update() override;
};