#include "shape2D.h"
#include "shaderProgram.h"

#include "glCore45.h"

void Shape2D::draw(const ShaderProgram& shader) {
    if (m_vao)
    {
        shader.bind();
        m_vao->bind();
        gl::DrawElements(gl::TRIANGLES, m_ibo->getCount(), gl::UNSIGNED_SHORT, nullptr);
    }
}

void Shape2D::commitShape(std::unique_ptr<VertexBuffer> vbo, std::unique_ptr<VertexArray> vao, std::unique_ptr<IndexBuffer> ibo)
{
    m_vbo = std::move(vbo);
    m_vao = std::move(vao);
    m_ibo = std::move(ibo);
}
