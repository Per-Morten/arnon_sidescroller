/// ArnonSidescroller

#ifndef SHAPE2D_QUAD_H
#define SHAPE2D_QUAD_H

#include "shape2D.h"

#include "glm/vec2.hpp"

class Quad : public Shape2D
{
public:
    Quad(const glm::vec2& size);

};

#endif // SHAPE2D_QUAD_H
