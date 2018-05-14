#include "vertexArray.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"

#include "glCore45.h"

VertexArray::VertexArray()
{
    gl::CreateVertexArrays(1, &m_name);
}

VertexArray::VertexArray(VertexArray&& other) noexcept : m_name(other.m_name)
{
    other.m_name = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
    if (this == &other) return *this;

    // Destructor Work
    gl::DeleteVertexArrays(1, &m_name);

    // Steal Resources
    m_name = other.m_name;
    other.m_name = 0;

    return *this;
}

VertexArray::~VertexArray() noexcept
{
    gl::DeleteVertexArrays(1, &m_name);
}

void VertexArray::bind() const
{
    gl::BindVertexArray(m_name);
}

void VertexArray::unbind() const
{
    gl::BindVertexArray(0);
}

unsigned VertexArray::name() const
{
    return m_name;
}

void VertexArray::setAttribute(unsigned attribute, unsigned binding, int size, unsigned type, unsigned offset, bool normalize /*= false*/)
{
    gl::VertexArrayAttribBinding(m_name, attribute, binding);
    gl::VertexArrayAttribFormat(m_name, attribute, size, type, (normalize ? gl::TRUE_ : gl::FALSE_), offset);
    gl::EnableVertexArrayAttrib(m_name, attribute);
}

void VertexArray::setIntegerAttribute(unsigned attribute, unsigned binding, int size, unsigned type, unsigned offset)
{
    gl::VertexArrayAttribBinding(m_name, attribute, binding);
    gl::VertexArrayAttribIFormat(m_name, attribute, size, type, offset); // Integral Version
    gl::EnableVertexArrayAttrib(m_name, attribute);
}

void VertexArray::setAttributeAsInstanced(unsigned binding, unsigned divisor)
{
    gl::VertexArrayBindingDivisor(m_name, binding, divisor);
}

void VertexArray::disableAttribute(unsigned attribute)
{
    gl::DisableVertexArrayAttrib(m_name, attribute);
}

void VertexArray::setVertexBuffer(const VertexBuffer& vbo, unsigned binding, int stride, ptrdiff_t offset)
{
    gl::VertexArrayVertexBuffer(m_name, binding, vbo.name(), offset, stride);
}

void VertexArray::setIndexBuffer(const IndexBuffer& ibo)
{
    gl::VertexArrayElementBuffer(m_name, ibo.name());
}
