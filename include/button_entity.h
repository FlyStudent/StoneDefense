#pragma once

#include <functional>

#include "entity.h"
#include "primitive2.h"
#include "enums.h"
#include "vector2.h"

class Game;
class Button;

class ButtonEntity : public Entity
{
private:
    Button* m_button;

public:
    ButtonEntity(Game&, Box box, Texture texture, std::function<void(void)>);
    ~ButtonEntity() = default;

    Texture  m_texture = Texture::NONE;

    void draw() override;
};
