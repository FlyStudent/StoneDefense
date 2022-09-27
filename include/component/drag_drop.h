#pragma once

#include "enums.h"

#include "component/component.h"

class Entity;

class DragDrop : public Component
{
private:
    Entity* m_entityDragged = nullptr;
public:
    DragDrop(Entity&);
    ~DragDrop() = default;

    void    activeDrag(Entity*);

    void    update() override;
};
