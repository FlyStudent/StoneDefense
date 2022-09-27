#pragma once

#include "component/component.h"

class Entity;

class MouseMove : public Component
{
private:

public:
    MouseMove(Entity&);
    ~MouseMove() = default;

    void    update();
};