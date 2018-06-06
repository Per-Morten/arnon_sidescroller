#include "shape2D_circle.h"

#include <vector>
#include <cstdint>

#include "glCore45.h"
#include "glm/trigonometric.hpp"
#include "glm/gtc/constants.hpp"

// Circle points (should probably be a parameter in the future)
template<typename T>
constexpr T accuracy = 32u;

Circle::Circle(float radius)
{
    std::vector<Shape2DVertex> vertices{{{0.f, 0.f}, {0.5f, 0.5f}, glm::vec4(1.f)}};
    std::vector<uint16_t> indices;

    // Generate the circle vertices
    for (int i = 0; i != accuracy<int>; ++i)
    {
        const auto xPos = glm::cos((i / accuracy<float>) * glm::two_pi<float>());
        const auto yPos = glm::sin((i / accuracy<float>) * glm::two_pi<float>());

        Shape2DVertex vert;
        vert.position = { xPos * radius, yPos * radius };
        vert.texCoord = { (xPos + 1.f) / 2.f, (yPos + 1.f) / 2.f };
        vert.color = glm::vec4(1.f);

        vertices.push_back(vert);
    }

    // Generate the cirlce indices
    for(uint16_t i = 1; i != accuracy<uint16_t>; ++i)
    {
        indices.emplace_back(0u);
        indices.emplace_back(i);
        indices.emplace_back(i + 1);
    }

    // Final triangle
    indices.emplace_back(0u);
    indices.emplace_back(accuracy<uint16_t>);
    indices.emplace_back(1);

    // Create VBO and IBO from the data created above
    auto vbo = std::make_unique<VertexBuffer>(vertices.data(), sizeof(Shape2DVertex) * vertices.size());
    auto ibo = std::make_unique<IndexBuffer>(indices.data(), sizeof(uint16_t) * indices.size(), static_cast<uint16_t>(indices.size()));

    // Create VAO and attach the VBO to binding 0, and set the IBO
    auto vao = std::make_unique<VertexArray>();
    vao->setVertexBuffer(*vbo, 0, sizeof(Shape2DVertex));
    vao->setIndexBuffer(*ibo);

    // Set the vertex attributes
    vao->setAttribute(0, 0, 2, gl::FLOAT, 0);
    vao->setAttribute(1, 0, 2, gl::FLOAT, offsetof(Shape2DVertex, texCoord));
    vao->setAttribute(2, 0, 4, gl::FLOAT, offsetof(Shape2DVertex, color));

    // Commit the shape
    commitShape(std::move(vbo), std::move(vao), std::move(ibo));
}
