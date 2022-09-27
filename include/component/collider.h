#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "primitive2.h"
#include "component/component.h"

class Entity;

class Collider : public Component
{
private:
    uint64_t m_tag = 0;
    uint64_t m_mask = 0;

public:
    Collider() = default;
    Collider(Entity&);
    ~Collider() = default;

    std::unique_ptr<Primitive2>  m_collider;

    void     setTag(uint64_t);
    void     setMask(uint64_t);
    int      getTag() const;
    int      getMask() const;
};
