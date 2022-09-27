
#include <memory>

#include "game.h"

#include "button_entity.h"
#include "component/button.h"

ButtonEntity::ButtonEntity(Game& game, Box box, Texture texture, std::function<void(void)> event)
: Entity(game, box.m_center, false), m_texture(texture)
{
    components.emplace_back(std::make_unique<Button>(*this, box, event));
    m_button = reinterpret_cast<Button*>(components.back().get());
    m_button->m_isActivate = true;
    m_layer = 3;
}

void ButtonEntity::draw()
{
    auto gp = m_game.m_gp;

    GPTexture texture = m_game.m_textures[(int)m_texture];
    Vector2 scale = m_button->isOverlapped ? Vector2(1.2f, 1.2f) : Vector2(1.f, 1.f);
    gpDrawTextureEx(gp, texture, {0.f, 0.f, (float)texture.width, (float)texture.height}, m_button->getBox().m_center, 0.f, scale, nullptr, GP_CWHITE);
}
