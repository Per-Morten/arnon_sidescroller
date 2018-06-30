#ifndef VERTEXTYPES_H
#define VERTEXTYPES_H

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

// Sprite vertex
struct SpriteVertex
{
    glm::vec3 position;
    glm::vec2 texCoord;
    glm::vec4 color;
};

#endif // VERTEXTYPES_H
