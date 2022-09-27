#pragma once

#include <memory>
#include <functional>

#include "game.h"
#include "primitive2.h"
#include "component.h"

class BoxCollider;

class Button : public Component
{
private:
    std::unique_ptr<BoxCollider>    m_collider;
    std::function<void(void)>       m_event;

    //bool                        m_isClicked = false;
public:
    Button(Entity&, Box, std::function<void(void)>);
    ~Button() = default;

    bool isOverlapped = false;

    Box  getBox() const {return m_collider->m_box;}

    void update();
};