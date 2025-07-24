#include "textureManager.h"

std::shared_ptr<Texture2D> TextureManager::LoadTexture(const std::string &path)
{
    auto it = m_textures.find(path);
    if (it != m_textures.end())
    {
        return it->second;
    }

    Texture2D rawTexture = ::LoadTexture(path.c_str());
    if (rawTexture.id == 0)
    {
        LOG_WARN("Failed to load texture: {}", path);
        return nullptr;
    }

    auto texturePtr = std::shared_ptr<Texture2D>(new Texture2D(rawTexture),
                                                 [path](Texture2D *tex)
                                                 {
                                                     ::UnloadTexture(*tex);
                                                     LOG_INFO("Unload Texture " + path);
                                                     delete tex;
                                                 });

    m_textures[path] = texturePtr;
    LOG_INFO("Load Texture " + path);
    return texturePtr;
}

void TextureManager::UnloadAll()
{
    m_textures.clear();
    LOG_INFO("Unload all Textures");
}

bool TextureManager::FlipTextureHorizontal(Texture2D &texture)
{
    if (texture.id == 0)
    {
        LOG_WARN("Cannot resize texture: invalid texture ID");
        return false;
    }
    try
    {
        Image image = LoadImageFromTexture(texture);
        ImageFlipHorizontal(&image);
        UnloadTexture(texture);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        return true;
    }
    catch (const std::exception &ex)
    {
        LOG_WARN("Failed to flip texture vertical: {}", ex.what());
        return false;
    }
}

bool TextureManager::FlipTextureVertical(Texture2D &texture)
{
    if (texture.id == 0)
    {
        LOG_WARN("Cannot resize texture: invalid texture ID");
        return false;
    }
    try
    {
        Image image = LoadImageFromTexture(texture);
        ImageFlipVertical(&image);
        UnloadTexture(texture);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        return true;
    }
    catch (const std::exception &ex)
    {
        LOG_WARN("Failed to flip texture vertical: {}", ex.what());
        return false;
    }
}
bool TextureManager::RotateTexture(Texture2D &texture, int degrees)
{
    if (degrees < 0 || degrees >= 360)
    {
        LOG_WARN("Cannot rotate texture: invalid degrees provided");
        return false;
    }
    if (texture.id == 0)
    {
        LOG_WARN("Cannot resize texture: invalid texture ID");
        return false;
    }
    try
    {
        Image image = LoadImageFromTexture(texture);
        ImageRotate(&image, degrees);
        UnloadTexture(texture);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        return true;
    }
    catch (const std::exception &ex)
    {
        LOG_WARN("Failed to rotate texture: {}", ex.what());
        return false;
    }
}

bool TextureManager::ResizeTexture(Texture2D &texture, float newWidth, float newHeight)
{

    if (newWidth < 0 || newHeight < 0)
    {
        LOG_WARN("Cannot resize texture: negative dimensions provided");
        return false;
    }
    if (texture.id == 0)
    {
        LOG_WARN("Cannot resize texture: invalid texture ID");
        return false;
    }
    try
    {
        Image image = LoadImageFromTexture(texture);
        ImageResize(&image, newWidth, newHeight);
        UnloadTexture(texture);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        return true;
    }
    catch (const std::exception &ex)
    {
        LOG_WARN("Failed to resize texture: {}", ex.what());
        return false;
    }
}
