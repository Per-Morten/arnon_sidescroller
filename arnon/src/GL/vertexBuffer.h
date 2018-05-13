/// ArnonSideScroller

/* 
 * Abstraction of an OpenGL Vertex Buffer
 */

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <cstddef>
#include <cstdint>

class VertexBuffer final
{
private:
    // The OpenGL Name
    uint32_t m_name = 0;

public:
    // Construct from known data of size
    VertexBuffer(const void* data, ptrdiff_t dataSize);

    // Copy Ctor
    VertexBuffer(const VertexBuffer& other);

    // Copy Assignment
    VertexBuffer& operator=(const VertexBuffer& other);

    // Move Ctor
    VertexBuffer(VertexBuffer&& other);

    // Move Assignment
    VertexBuffer& operator=(VertexBuffer&& other);

    // Dtor
    ~VertexBuffer();

    // Bind the vertex buffer to the gl array buffer
    void bind() const;

    // Unbind the vertex buffer from the gl array buffer
    void unbind() const;

    // Return the OpenGL name of the buffer
    const unsigned name() const;
    
    // Reset buffer and exchange data
    void resetData(const void* newData, ptrdiff_t newSize);

private:
    // Clear current buffer data and re-initialize with data copied from source
    void resetBufferDataFromCopy(const VertexBuffer& source);
};



#endif // VERTEXBUFFER_H
