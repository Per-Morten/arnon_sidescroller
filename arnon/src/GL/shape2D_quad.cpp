#include "shape2D_quad.h"

#include <vector>
#include <cstdint>

#include "glCore45.h"

Quad::Quad(const glm::vec2& size)
{
    std::vector<uint16_t> indices{ 0, 1, 2, 2, 3, 0 };

    std::vector<Shape2DVertex> vertices{ { -size / 2.f, {0.f, 0.f}, glm::vec4(1.f) },
                                         { {size.x / 2.f, -size.y / 2.f }, {1.f, 0.f}, glm::vec4(1.f) },
                                         {  size / 2.f, {1.f, 1.f}, glm::vec4(1.f) },
                                         { {-size.x / 2.f, size.y / 2.f}, {0.f, 1.f}, glm::vec4(1.f) } };

    // Create VBO and IBO from the data created above
    auto vbo = std::make_unique<VertexBuffer>(vertices.data(), sizeof(Shape2DVertex) * vertices.size());
    auto ibo = std::make_unique<IndexBuffer>(indices.data(), sizeof(uint16_t) * indices.size(), static_cast<uint16_t>(indices.size()));
    
    // Create VAO and attach the VBO to binding 0, and set the IBO
    auto vao = std::make_unique<VertexArray>();
    vao->setVertexBuffer(*vbo, 0, sizeof(Shape2DVertex));
    // vao->setIndexBuffer(*ibo); #TODO : Investigate why this works, but produces a GL error when not also bound.. Hmmm??

    // Set the vertex attributes
    vao->setAttribute(0, 0, 2, gl::FLOAT, 0);
    vao->setAttribute(1, 0, 2, gl::FLOAT, offsetof(Shape2DVertex, texCoord));
    vao->setAttribute(2, 0, 4, gl::FLOAT, offsetof(Shape2DVertex, color));
    
    // Commit the shape
    commitShape(std::move(vbo), std::move(vao), std::move(ibo));
}
