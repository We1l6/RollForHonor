#pragma once

/**
 * @file textureManager.h
 * @brief Texture Manager
 * @details With Meyer's Singleton, I retrieve instances and load Textures.
 * @author We1l6.f
 * @date 13/06/2025
 */

#include "../../loggerManager/loggerManager.h"
#include "raylib.h"
#include <memory>
#include <string>
#include <unordered_map>

class TextureManager {
public:
  std::shared_ptr<Texture2D> LoadTexture(const std::string &path);
  void UnloadAll();

  bool FlipTextureVertical(Texture2D &texture);
  bool FlipTextureHorizontal(Texture2D &texture);
  bool RotateTexture(Texture2D &texture, int degrees);
  bool ResizeTexture(Texture2D &texture, float newWidth, float newHeight);
  TextureManager() = default;
  ~TextureManager() { UnloadAll(); }
private:

  std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_textures;
};
