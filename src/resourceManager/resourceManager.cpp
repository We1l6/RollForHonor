#include "resourceManager.h"

std::shared_ptr<Texture2D>
ResourceManager::LoadTexture(const std::string &path) {
  return TextureManager::GetInstance().LoadTexture(path);
}

bool ResourceManager::FlipTexture(Texture2D &texture, bool horizontal,
                                  bool vertical) {
  auto &tm = TextureManager::GetInstance();
  bool success = true;

  if (vertical) {
    success &= tm.FlipTextureVertical(texture);
  }
  if (horizontal) {
    success &= tm.FlipTextureHorizontal(texture);
  }

  return success;
}

bool ResourceManager::ResizeTexture(Texture2D &texture, float newWidth,
                                    float newHeight) {
  auto &tm = TextureManager::GetInstance();
  return tm.ResizeTexture(texture, newWidth, newHeight);
}

std::shared_ptr<Sound> ResourceManager::LoadSound(const std::string &path) {
  return SoundManager::GetInstance().LoadSound(path);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string &path) {
  return FontManager::GetInstance().LoadFont(path);
}

static void UnloadTextures() { TextureManager::GetInstance().UnloadAll(); }
static void UnloadSounds() { SoundManager::GetInstance().UnloadAll(); }
static void UnloadFonts() { FontManager::GetInstance().UnloadAll(); }