#include "resourceManager.h"

std::shared_ptr<Texture2D>
ResourceManager::LoadTexture(const std::string &path) {
  return TextureManager::LoadTexture(path);
}

std::shared_ptr<Sound> ResourceManager::LoadSound(const std::string &path) {
  return SoundManager::LoadSound(path);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string &path) {
  return FontManager::LoadFont(path);
}

static void UnloadTextures() { TextureManager::UnloadAll(); }
static void UnloadSounds() { SoundManager::UnloadAll(); }
static void UnloadFonts() { SoundManager::UnloadAll(); }