/// ArnonSidescroller

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <cstdint>

class IndexBuffer;
class VertexBuffer;

class VertexArray
{
private:
    // The OpenGL Name
    uint32_t m_name = 0;

public:
    // Default Ctor
    VertexArray();

    // Move Ctor
    VertexArray(VertexArray&& other);

    // Move Ass
    VertexArray& operator=(VertexArray&& other);

    // Dtor
    ~VertexArray();

    // Bind Vertex Array
    void bind() const;

    // Unbind Vertex Array
    void unbind() const;

    //************************************
    // Method:    VertexArray::name
    // Access:    public 
    // Brief:     Get the OpenGL Name of the Vertex Array
    // Example:   gl::BindVertexArray(vao.name());
    //************************************
    const unsigned name() const;

    // Add an attribute to the vertex array. For a vec4, you would add(4, gl::FLOAT, ...)
    void setAttribute(unsigned attribute, unsigned binding, int size, unsigned type, unsigned offset, bool normalize = false);
    
    // Add a NOT normalized integral vertex attribute. Type must be of an integral type.
    void setIntegerAttribute(unsigned attribute, unsigned binding, int size, unsigned type, unsigned offset);

    // Set the given VBO binding to be instanced per divisor instance
    void setAttributeAsInstanced(unsigned binding, unsigned divisor);

    // Remove and disable the given attribute
    void disableAttribute(unsigned attribute);

    // Set the vertex buffer for the given binding point that has the Vertex Array attribute data
    void setVertexBuffer(const VertexBuffer& vbo, unsigned binding, int stride, ptrdiff_t offset=0);
    
    // Set the index buffer to use for indexed drawing
    void setIndexBuffer(const IndexBuffer& ibo);
};


#endif // VERTEXARRAY_H
