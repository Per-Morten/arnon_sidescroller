/// ArnonSidescroller

/*
 * Abstracts an OpenGL framebuffer. Currently
 * has a fixed layout. Texture attached to the
 * Color0 attachment, and a renderbuffer attached
 * to the depth/stencil attachment.
 */

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>

#include "glm/vec2.hpp"

class Framebuffer final
{
private:
    // The framebuffer OpenGL Name
    uint32_t m_name = 0;

    // Texture for Color Attachment 0
    uint32_t m_texture = 0;

    // Renderbuffer for Depth / Stencil
    uint32_t m_renderbuffer = 0;

public:
    // Ctor from a size
    Framebuffer(const glm::ivec2& size);

    // Copy Ctor
    Framebuffer(const Framebuffer& other);

    // Copy Ass
    Framebuffer& operator=(const Framebuffer& other);

    // Move Ctor
    Framebuffer(Framebuffer&& other) noexcept;

    // Move Ass
    Framebuffer& operator=(Framebuffer&& other) noexcept;

    // Dtor
    ~Framebuffer();

    // Bind the framebuffer (to both read and write)
    void bind();

    // Bind the framebuffer as a write framebuffer
    void bindWriteonly();

    // Bind the framebuffer as a read framebuffer
    void bindReadonly();

    // Unbind the framebuffer (from both read and write)
    void unbind();

    // Bind the framebuffer color texture to a texture binding point
    void bindTexture(unsigned bindingPoint);

    // Unbind the framebuffer color texture from a texture binding point
    void unbindTexture(unsigned bindingPoint);

    // Recreate the framebuffer with a new size
    void resetToNewSize(const glm::ivec2& size);

private:
    // Check with OpenGL if whether the framebuffer is complete
    bool validateFramebuffer() const;

    // Create the framebuffer
    void createFramebuffer(const glm::ivec2& size);

    // Create the texture attachment
    void createTexture(const glm::ivec2& size);

    // Create the renderbuffer for depth/stencil
    void createRenderbuffer(const glm::ivec2& size);

    // Reset this framebuffer to be a copy of the other
    void resetFromCopy(const Framebuffer& other);
};

#endif // FRAMEBUFFER_H
