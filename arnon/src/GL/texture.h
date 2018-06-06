/// ArnonSidescroller

/*
 * For loading and binding Textures to the OpenGL context.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>
#include <string>

class Texture final
{
private:
    // The OpenGL Texture Name
    uint32_t m_name = 0;

public:
    // Default ctor
    Texture() = default;

    // Construct from filepath
    Texture(const std::string& filepath);

    // #TODO : Texture(const std::filesystem::path& filepath);

    // Move Ctor
    Texture(Texture&& other) noexcept;

    // Move Ass
    Texture& operator=(Texture&& other) noexcept;

    // Dtor
    ~Texture();

    // Bind to given bindingPoint
    void bind(const unsigned bindingPoint);

    // Unbind from given binding point
    void unbind(const unsigned bindingPoint);

    // Load an image file into this texture
    void loadFromFile(const std::string& filepath);

private:
    // Check if the texture is a valid OpenGL object
    bool isValid() const;

};

#endif // TEXTURE_H
