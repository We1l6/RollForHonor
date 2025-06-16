#pragma once

/**
 * @file textureManager.h
 * @brief Texture Manager
 * @details With Meyer's Singleton, I retrieve instances and load Textures.
 * @author We1l6.f
 * @date 13/06/2025
 */

#include "raylib.h"
#include <memory>
#include <string>
#include <unordered_map>

class TextureManager {
public:
  static TextureManager &GetInstance();
  TextureManager(const TextureManager &) = delete;
  TextureManager &operator=(const TextureManager &) = delete;
  std::shared_ptr<Texture2D> LoadTexture(const std::string &path);
  void UnloadAll();

private:
  TextureManager() = default;
  ~TextureManager() { UnloadAll(); }
  std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_textures;
};
