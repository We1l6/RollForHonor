#include "resourceManager.h"

std::shared_ptr<Texture2D>
ResourceManager::LoadTexture(const std::string &path) {
  return TextureManager::GetInstance().LoadTexture(path);
}

std::shared_ptr<Sound> ResourceManager::LoadSound(const std::string &path) {
  return SoundManager::GetInstance().LoadSound(path);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string &path) {
  return FontManager::GetInstance().LoadFont(path);
}

void UnloadTextures() { TextureManager::GetInstance().UnloadAll(); }
void UnloadSounds() { SoundManager::GetInstance().UnloadAll(); }
void UnloadFonts() { FontManager::GetInstance().UnloadAll(); }