#include "vertexBuffer.h"

#include "glCore45.h"

// #TODO : Support use of NamedBufferStorage for immutable storage benefits
// #TODO : Support use of MapBufferRange to offer more control of data resets

VertexBuffer::VertexBuffer(const void* data, ptrdiff_t dataSize)
{
    gl::CreateBuffers(1, &m_name);
    gl::NamedBufferData(m_name, dataSize, data, gl::STATIC_DRAW);
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other)
{
    if (this == &other) return *this;

    // Destructor Work
    gl::DeleteBuffers(1, &m_name);

    // Steal Resources
    m_name = other.m_name;
    other.m_name = 0;

    return *this;
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) : m_name(other.m_name)
{
    other.m_name = 0;
}

VertexBuffer::VertexBuffer(const VertexBuffer& other)
{
    resetBufferDataFromCopy(other);
}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& other)
{
    if (this == &other) return *this;
    resetBufferDataFromCopy(other);
    return *this;
}

VertexBuffer::~VertexBuffer()
{
    gl::DeleteBuffers(1, &m_name);
}

void VertexBuffer::bind() const
{
    gl::BindBuffer(gl::ARRAY_BUFFER, m_name);
}

void VertexBuffer::unbind() const
{
    gl::BindBuffer(gl::ARRAY_BUFFER, 0);
}

const unsigned VertexBuffer::name() const
{
    return m_name;
}

void VertexBuffer::resetData(const void* newData, ptrdiff_t newSize)
{
    gl::NamedBufferData(m_name, newSize, newData, gl::STATIC_DRAW);
}

void VertexBuffer::resetBufferDataFromCopy(const VertexBuffer& source)
{
    gl::DeleteBuffers(1, &m_name);
    gl::CreateBuffers(1, &m_name);

    int size;
    gl::GetNamedBufferParameteriv(source.m_name, gl::BUFFER_SIZE, &size);
    gl::NamedBufferData(m_name, size, nullptr, gl::STATIC_DRAW);
    gl::CopyNamedBufferSubData(source.m_name, m_name, 0, 0, size);
}
