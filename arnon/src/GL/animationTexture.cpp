#include "animationTexture.h"
#include "debug/arnlog.h"
#include "debug/asserts.h"

#include "GL/stb_image.h"
#include "GL/glCore45.h"

AnimationTexture::AnimationTexture(const std::filesystem::path& baseTexture, unsigned numberOfFrames)
{
    createFromFile(baseTexture, numberOfFrames);
}

AnimationTexture::~AnimationTexture()
{
    gl::DeleteTextures(1, &m_name);
}

void AnimationTexture::bind(unsigned textureUnit)
{
    gl::BindTextureUnit(textureUnit, m_name);
}

void AnimationTexture::createFromFile(const std::filesystem::path& baseTexture, unsigned numberOfFrames)
{
    gl::CreateTextures(gl::TEXTURE_2D_ARRAY, 1, &m_name);
    allocateTextureStorage(baseTexture, numberOfFrames);
   
    // Get file name and extension
    const auto file = baseTexture.stem().string();
    const auto ext  = baseTexture.extension().string();

    // Used for image loading
    int w, h, comp;

    // Load frames (first frame number is 1)
    for (unsigned i = 1; i <= numberOfFrames; ++i)
    {
        // Construct the current framePath from provided basePath
        const auto currentFramePath = baseTexture.parent_path() / (file + std::to_string(i) + ext);
        logDebug("Created path: {}", currentFramePath);

        // Load and assign texture data to correct level
        unsigned char* pixels = stbi_load(currentFramePath.string().c_str(), &w, &h, &comp, 0);
        gl::TextureSubImage3D(m_name, 0, 0, 0, i - 1, w, h, 1, gl::RGBA, gl::UNSIGNED_BYTE, pixels);

        // Clean up
        stbi_image_free(pixels);
    }
}

void AnimationTexture::allocateTextureStorage(const std::filesystem::path &baseTexture, unsigned numberOfFrames)
{
    // Find required file parts to get info from first frame
    const auto fileString = baseTexture.stem().string();
    const auto extString = baseTexture.extension().string();

    // Get animation frame dimensions
    int w, h;
    stbi_info((baseTexture.parent_path() / (fileString + "1" + extString)).string().c_str() , &w, &h, nullptr);

    // Allocate
    gl::TextureStorage3D(m_name, 1, gl::RGBA8, w, h, numberOfFrames);
}
