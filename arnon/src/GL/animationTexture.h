/// ArnonSidescroller

/* 
 * \brief Contains all required data for an animation
 */

#ifndef ANIMATIONTEXTURE_H
#define ANIMATIONTEXTURE_H

#include <filesystem>

#include "glm/vec2.hpp"

class AnimationTexture
{
private:
    // The OpenGL Name
    unsigned m_name = 0;

public:
    // Create an animation texture from a basepath and n frames following that
    AnimationTexture(const std::filesystem::path& baseTexture, unsigned numberOfFrames);

    ~AnimationTexture();

    /*!
     * \brief Bind the Animation texture to the provided Texture Unit
     */
    void bind(unsigned textureUnit);

private:
    // Create the texture and load all paths from the base file
    void createFromFile(const std::filesystem::path& baseTexture, unsigned numberOfFrames);

    // Allocates a 3D texture space using the base texture and a number of frames
    void allocateTextureStorage(const std::filesystem::path& baseTexture, unsigned numberOfFrames);

};


#endif // ANIMATIONTEXTURE_H
