#pragma once
#include "raylib.h"
#include <memory>
#include <string>
#include <unordered_map>

class TextureManager {
public:
  static std::shared_ptr<Texture2D> LoadTexture(const std::string &path);
  static void UnloadAll();

private:
  static std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_textures;
};
