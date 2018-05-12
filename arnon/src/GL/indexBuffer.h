/// ArnonSideScroller

/*
 * Abstraction of OpenGL indexbuffer
 */

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <cstddef>

class IndexBuffer final
{
private:
    // The OpenGL Name
    unsigned m_name = 0;

    // Number of indices
    unsigned m_count = 0;

public:
    // Ctor from data, size and number of indices
    IndexBuffer(const void* data, ptrdiff_t dataSize, unsigned count);

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
};

#endif // INDEXBUFFER_H
