/// ArnonSidescroller

#ifndef SHAPE2D_H
#define SHAPE2D_H

#include "vertexArray.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"

#include <memory>

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

class ShaderProgram;

struct Shape2DVertex
{
    glm::vec2 position;
    glm::vec2 texCoord;
    glm::vec4 color;
};

class Shape2D
{
private:
    // Shape VertexBuffer
    std::unique_ptr<VertexBuffer> m_vbo = nullptr;

    // Shape VertexArray
    std::unique_ptr<VertexArray> m_vao = nullptr;

    // Shape IndexBuffer
    std::unique_ptr<IndexBuffer> m_ibo = nullptr;

public:
    Shape2D() = default;

    virtual ~Shape2D() noexcept = default;

    // Should be changed so that a renderer takes a Shape2D and draws it instead
    void draw(const ShaderProgram& shader);

protected:
    // Call to commit the final shape data
    void commitShape(std::unique_ptr<VertexBuffer> vbo, std::unique_ptr<VertexArray> vao, std::unique_ptr<IndexBuffer> ibo);

};

#endif // SHAPE2D_H
