#include "framebuffer.h"

Framebuffer::Framebuffer(const glm::ivec2& size)
{
    resetToNewSize(size);
}

Framebuffer::Framebuffer(const Framebuffer& other)
{
    resetFromCopy();
}

Framebuffer::Framebuffer& Framebuffer::operator=(const Framebuffer& other)
{
    if (this == &other) return *this;

    // ResetFromCopy will also delete existing fb/tex/rb so not necessary to do so here
    resetFromCopy(other);

    return *this;
}

Framebuffer::Framebuffer(Framebuffer&& other) : m_name(other.m_name), m_renderbuffer(other.m_renderbuffer), m_texture(other.m_texture)
{
    other.m_name = 0;
    other.m_texture = 0;
    other.m_renderbuffer = 0;
}

Framebuffer::Framebuffer& Framebuffer::operator=(Framebuffer&& other)
{
    // Protect / Delete
    if (this == &other) return *this;
    gl::DeleteFramebuffers(1, &m_name);
    gl::DeleteTextures(1, &m_texture);
    gl::DeleteRenderbuffers(1, &m_renderbuffer);

    // Steal
    m_name = other.m_name;
    m_texture = other.m_texture;
    m_renderbuffer = other.m_renderbuffer;

    // Clean up
    other.m_name = 0;
    other.m_texture = 0;
    other.m_renderbuffer = 0;

    return *this;
}

Framebuffer::~Framebuffer()
{
    gl::DeleteFramebuffers(1, &m_name);
    gl::DeleteTextures(1, &m_texture);
    gl::DeleteRenderbuffers(1, &m_renderbuffer);
}

void Framebuffer::bind()
{
    gl::BindFramebuffer(gl::FRAMEBUFFER, m_name);
}

void Framebuffer::bindReadonly()
{
    gl::BindFramebuffer(gl::READ_FRAMEBUFFER, m_name);
}

void Framebuffer::bindWriteonly()
{
    gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, m_name);
}

void Framebuffer::unbind()
{
    gl::BindFramebuffer(gl::FRAMEBUFFER, 0);
}

void Framebuffer::resetToNewSize(const glm::ivec2& size)
{
    // Assume that we have valid objects and just delete them by default
    gl::DeleteFramebuffers(1, &m_name);
    gl::DeleteTextures(1, &m_texture);
    gl::DeleteRenderbuffers(1, &m_renderbuffer);

    // Then start re-creating them
    createTexture(size);
    createRenderbuffer(size);
    createFramebuffer(size);

    // Ensure everything is in order
    if (!validateFramebuffer())
    {
        // #TODO: Log error or throw

        gl::DeleteFramebuffers(1, &m_name);
        gl::DeleteTextures(1, &m_texture);
        gl::DeleteRenderbuffers(1, &m_renderbuffer);
    }
}

void Framebuffer::createFramebuffer(const glm::ivec2& size)
{
    // Simply Attach the stuff created in the earlier steps
    gl::CreateFramebuffers(1, &m_name);
    gl::NamedFramebufferTexture(m_name, gl::COLOR_ATTACHMENT0, m_texture, 0);
    gl::NamedFramebufferRenderbuffer(m_name, gl::DEPTH_STENCIL_ATTACHMENT, gl::RENDERBUFFER, m_renderbuffer);
}

void Framebuffer::createTexture(const glm::ivec2& size)
{
    // Create texture
    gl::CreateTextures(gl::TEXTURE_2D, 1, &m_texture);
    gl::TextureStorage2D(m_texture, 1, gl::RGBA8, size.x, size.y);

    // Set default parameters
    gl::TextureParameteri(m_texture, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
    gl::TextureParameteri(m_texture, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
    gl::TextureParameteri(m_texture, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
    gl::TextureParameteri(m_texture, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
}

void Framebuffer::createRenderbuffer(const glm::ivec2& size)
{
    gl::CreateRenderbuffers(1, &m_renderbuffer);
    gl::NamedRenderbufferStorage(m_renderbuffer, gl::DEPTH24_STENCIL8, size.x, size.y);
}

const bool Framebuffer::validateFramebuffer() const
{
    return gl::CheckNamedFramebufferStatus(m_name, gl::FRAMEBUFFER) == gl::FRAMEBUFFER_COMPLETE;
}

void Framebuffer::resetFromCopy(const Framebuffer& other)
{
    // Get the size of the other one
    glm::ivec2 size;
    gl::GetNamedFramebufferParameteriv(other.m_name, gl::MAX_FRAMEBUFFER_WIDTH, &size.x);
    gl::GetNamedFramebufferParameteriv(other.m_name, gl::MAX_FRAMEBUFFER_HEIGHT, &size.y);

    // Create a framebuffer of the same size
    resetToNewSize(size);

    // Blit the other framebuffer into this one to also get it's current data
    gl::BlitNamedFramebuffer(other.m_name, m_name,
                             0, 0, size.x, size.y,
                             0, 0, size.x, size.y,
                             gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT | gl::STENCIL_BUFFER_BIT, gl::NEAREST);
}
