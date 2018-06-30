#ifndef SPRITE_H
#define SPRITE_H

#include "shape2D_quad.h"

#include <memory>

#include "glm/vec3.hpp"

class Texture;

class Sprite
{
private:
    // The texture used by this sprite
    Texture* m_texture = nullptr;

    // Quad used by this sprite, will default to white 10x10px quad
    std::unique_ptr<Quad> m_quad = nullptr;

    // Sprite tint color
    glm::vec3 m_color = glm::vec3(1.f);

public:
    Sprite() = default;

    // Initialize the sprite to show the given texture
    // Texture lifetime must outlive the sprite!
    Sprite(Texture& texture);

    // Set texture of the Sprite to the provided texture
    // Texture lifetime must outlive the sprite!
    void setTexture(Texture& texture);

    // Set the color tint of the sprite
    void setColor(const glm::vec3& color);

};

#endif // SPRITE_H
