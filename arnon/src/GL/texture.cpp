#include "texture.h"

#include <filesystem>

#include "glm/vec2.hpp"
#include "GL/glCore45.h"
#include "GL/stb_image.h"

Texture::Texture(const std::string& filepath)
{
    loadFromFile(filepath);
}

Texture::Texture(Texture&& other) : m_name(other.m_name)
{
    other.m_name = 0;
}

Texture& Texture::operator=(Texture&& other)
{
    if (this == &other) return *this;

    // Clean existing
    gl::DeleteTextures(1, &m_name);

    // Steal resources
    m_name = other.m_name;
    other.m_name = 0;

    return *this;
}

Texture::~Texture()
{
    gl::DeleteTextures(1, &m_name);
}

void Texture::bind(const unsigned bindingPoint)
{
    gl::BindTextureUnit(bindingPoint, m_name);
}

void Texture::unbind(const unsigned bindingPoint)
{
    gl::BindTextureUnit(bindingPoint, 0);
}

void Texture::loadFromFile(const std::string& filepath)
{
    // If already bound, delete old
    if (isValid()) gl::DeleteTextures(1, &m_name);

    // Load Image Data
    glm::ivec2 dimensions;
    auto* pixels = stbi_load(filepath.c_str(), &dimensions.x, &dimensions.y, nullptr, 0);

    // #TODO : Error the fuck out of here if pixels were not loaded!

    // Create accurately sized texture 
    gl::CreateTextures(gl::TEXTURE_2D, 1, &m_name);
    gl::TextureStorage2D(m_name, 1, gl::RGBA8, dimensions.x, dimensions.y);

    // Set Default texture parameters
    gl::TextureParameteri(m_name, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
    gl::TextureParameteri(m_name, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
    gl::TextureParameteri(m_name, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
    gl::TextureParameteri(m_name, gl::TEXTURE_MAG_FILTER, gl::LINEAR);

    // Initialize Image Data and Clean up
    gl::TextureSubImage2D(m_name, 0, 0, 0, dimensions.x, dimensions.y, gl::RGBA, gl::UNSIGNED_BYTE, pixels);
    stbi_image_free(pixels);
}

const bool Texture::isValid() const
{
    return m_name != 0;
}
