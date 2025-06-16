#include "textureManager.h"
#include "raylib.h"

std::shared_ptr<Texture2D>
TextureManager::LoadTexture(const std::string &path) {
  auto it = m_textures.find(path);
  if (it != m_textures.end()) {
    return it->second;
  }

  Texture2D rawTexture = ::LoadTexture(path.c_str());

  auto texturePtr =
      std::shared_ptr<Texture2D>(new Texture2D(rawTexture), [](Texture2D *tex) {
        ::UnloadTexture(*tex);
        delete tex;
      });

  m_textures[path] = texturePtr;
  return texturePtr;
}

void TextureManager::UnloadAll() { m_textures.clear(); }
TextureManager &TextureManager::GetInstance() {
  static TextureManager instance;
  return instance;
}