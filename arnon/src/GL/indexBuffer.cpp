#include "indexBuffer.h"

#include "glCore45.h"

IndexBuffer::IndexBuffer(const void* data, ptrdiff_t dataSize, uint16_t count) : m_count(count)
{
    gl::CreateBuffers(1, &m_name);
    gl::NamedBufferStorage(m_name, dataSize, data, 0);
}

IndexBuffer::IndexBuffer(const IndexBuffer& other) : m_count(other.m_count)
{
    resetBufferDataFromCopy(other);
}

IndexBuffer& IndexBuffer::operator=(const IndexBuffer& other)
{
    if (this == &other) return *this;

    m_count = other.m_count;

    // Copy GL Data
    gl::DeleteBuffers(1, &m_name);
    resetBufferDataFromCopy(other);

    return *this;
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) : m_name(other.m_name), m_count(other.m_count)
{
    other.m_name = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other)
{
    if (this == &other) return *this;

    // Destructor Work
    gl::DeleteBuffers(1, &m_name);

    // Steal Resources
    m_count = other.m_count;
    m_name = other.m_name;
    other.m_name = 0;
    other.m_count = 0;

    return *this;
}

IndexBuffer::~IndexBuffer()
{
    gl::DeleteBuffers(1, &m_name);
}

const unsigned IndexBuffer::name() const
{
    return m_name;
}

const unsigned IndexBuffer::getCount() const
{
    return m_count;
}

void IndexBuffer::bind() const
{
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, m_name);
}

void IndexBuffer::unbind() const
{
    gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, 0);
}

void resetBufferDataFromCopy(const IndexBuffer& other)
{
    gl::CreateBuffers(1, &m_name);

    // Get data size
    int dataSize;
    gl::GetNamedBufferParameteriv(other.m_name, gl::BUFFER_SIZE, &dataSize);

    // Initialize data store and copy the data across
    gl::NamedBufferStorage(m_name, dataSize, nullptr, 0);
    gl::CopyNamedBufferSubData(other.m_name, m_name, 0, 0, dataSize);
}
