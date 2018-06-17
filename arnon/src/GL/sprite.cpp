#include "sprite.h"
#include "texture.h"

Sprite::Sprite(Texture& texture)
{
    setTexture(texture);
}

void Sprite::setTexture(Texture& texture)
{
    auto size = texture.getSize();
    m_quad = std::make_unique<Quad>(size);
    m_texture = &texture;
}

void Sprite::setColor(const glm::vec3& color)
{
    m_color = color;
}
