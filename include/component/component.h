#pragma once

class Entity;
struct GPLib;

class Component
{
public:
    Component(Entity& en);
    virtual ~Component() = default;

    Entity&  m_entity;
    bool     m_isActivate;

    virtual void    update(){};
};


