/// ArnonSideScroller

/*
 * Abstraction of OpenGL indexbuffer
 */

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <cstddef>
#include <cstdint>

class IndexBuffer final
{
private:
    // The OpenGL Name
    uint32_t m_name = 0;

    // Number of indices
    uint16_t m_count = 0;

public:
    // Ctor from data, size and number of indices    [sized int to hint about index size]
    IndexBuffer(const void* data, ptrdiff_t dataSize, uint16_t count);

    // Copy Ctor
    IndexBuffer(const IndexBuffer& other);

    // Copy Assignment
    IndexBuffer& operator=(const IndexBuffer& other);

    // Move Ctor
    IndexBuffer(IndexBuffer&& other);

    // Move Assignment
    IndexBuffer& operator=(IndexBuffer&& other);

    // Dtor
    ~IndexBuffer();

    // Return the OpenGL name of the buffer
    const unsigned name() const;

    // Get the count of indices
    const unsigned getCount() const;

    // Bind to the element buffer
    void bind() const;

    // Unbind from the element buffer
    void unbind() const;

private:
    // Copy data from the other buffer into this one and re-initialize it
    void resetBufferDataFromCopy(const IndexBuffer& other);
};

#endif // INDEXBUFFER_H
